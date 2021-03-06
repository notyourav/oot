/*
 * File: z_en_rr.c
 * Overlay: ovl_En_Rr
 * Description: Like Like
 */

#include "z_en_rr.h"
#include "vt.h"

#define FLAGS 0x00000435

#define THIS ((EnRr*)thisx)

#define RR_MESSAGE_SHIELD (1 << 0)
#define RR_MESSAGE_TUNIC (1 << 1)
#define RR_MOUTH 4
#define RR_BASE 0

typedef enum {
    /* 0 */ REACH_NONE,
    /* 1 */ REACH_EXTEND,
    /* 2 */ REACH_STOP,
    /* 3 */ REACH_OPEN,
    /* 4 */ REACH_GAPE,
    /* 5 */ REACH_CLOSE
} EnRrReachState;

typedef enum {
    /* 0x1 */ RR_DAMAGE_STUN = 1,
    /* 0x2 */ RR_DAMAGE_FIRE,
    /* 0x3 */ RR_DAMAGE_ICE,
    /* 0x4 */ RR_DAMAGE_LIGHT_MAGIC,
    /* 0xB */ RR_DAMAGE_LIGHT_ARROW = 11,
    /* 0xC */ RR_DAMAGE_UNK_ARROW_1,
    /* 0xD */ RR_DAMAGE_UNK_ARROW_2,
    /* 0xE */ RR_DAMAGE_UNK_ARROW_3,
    /* 0xF */ RR_DAMAGE_NORMAL
} EnRrDamageEffect;

typedef enum {
    /* 0 */ RR_DROP_RANDOM_RUPEE,
    /* 1 */ RR_DROP_MAGIC,
    /* 2 */ RR_DROP_ARROW,
    /* 3 */ RR_DROP_FLEXIBLE,
    /* 4 */ RR_DROP_RUPEE_PURPLE,
    /* 5 */ RR_DROP_RUPEE_RED
} EnRrDropType;

void EnRr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnRr_InitBodySegments(EnRr* this, GlobalContext* globalCtx);

void EnRr_SetupDamage(EnRr* this);
void EnRr_SetupDeath(EnRr* this);

void EnRr_Approach(EnRr* this, GlobalContext* globalCtx);
void EnRr_Reach(EnRr* this, GlobalContext* globalCtx);
void EnRr_GrabPlayer(EnRr* this, GlobalContext* globalCtx);
void EnRr_Damage(EnRr* this, GlobalContext* globalCtx);
void EnRr_Death(EnRr* this, GlobalContext* globalCtx);
void EnRr_Retreat(EnRr* this, GlobalContext* globalCtx);
void EnRr_Stunned(EnRr* this, GlobalContext* globalCtx);

extern Gfx D_06000470[];

const ActorInit En_Rr_InitVars = {
    ACTOR_EN_RR,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RR,
    sizeof(EnRr),
    (ActorFunc)EnRr_Init,
    (ActorFunc)EnRr_Destroy,
    (ActorFunc)EnRr_Update,
    (ActorFunc)EnRr_Draw,
};

static char* sDropNames[] = {
    // "type 7", "small magic jar", "arrow", "fairy", "20 rupees", "50 rupees"
    "タイプ７  ", "魔法の壷小", "矢        ", "妖精      ", "20ルピー  ", "50ルピー  ",
};

static ColliderCylinderInit_Set3 sCylinderInit1 = {
    { COLTYPE_UNK10, 0x00, 0x09, 0x09, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x05, 0x01 },
    { 30, 55, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit_Set3 sCylinderInit2 = {
    { COLTYPE_UNK10, 0x00, 0x0D, 0x0D, COLSHAPE_CYLINDER },
    { 0x00, { 0xFFCFFFFF, 0x00, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 }, 0x01, 0x01, 0x01 },
    { 20, 20, -10, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    0x00, 0xF2, 0xF1, 0xF2, 0x10, 0xF2, 0xF2, 0x10, 0xF1, 0xF2, 0xF4, 0x24, 0x34, 0xBF, 0xD4, 0xCF,
    0xEF, 0x24, 0x33, 0x4A, 0x00, 0x00, 0xF1, 0xF4, 0xF2, 0xF2, 0xF8, 0xF4, 0xEA, 0x00, 0x00, 0x00,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(naviEnemyId, 55, ICHAIN_CONTINUE),
    ICHAIN_U8(unk_1F, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(unk_4C, 30, ICHAIN_STOP),
};

void EnRr_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnRr* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.health = 4;
    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_SetCylinder_Set3(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    Collider_InitCylinder(globalCtx, &this->collider2);
    Collider_SetCylinder_Set3(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    Actor_SetHeight(&this->actor, 30.0f);
    this->actor.scale.y = 0.013f;
    this->actor.scale.x = this->actor.scale.z = 0.014f;
    this->actor.colChkInfo.mass = 0xFF;
    this->actor.velocity.y = this->actor.speedXZ = 0.0f;
    this->actor.gravity = -0.4f;
    this->actionTimer = 0;
    this->eatenShield = 0;
    this->eatenTunic = 0;
    this->retreat = false;
    this->grabTimer = 0;
    this->invincibilityTimer = 0;
    this->effectTimer = 0;
    this->hasPlayer = false;
    this->stopScroll = false;
    this->ocTimer = 0;
    this->reachState = this->isDead = false;
    this->actionFunc = EnRr_Approach;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].height = this->bodySegs[i].heightTarget = this->bodySegs[i].scaleMod.x =
            this->bodySegs[i].scaleMod.y = this->bodySegs[i].scaleMod.z = 0.0f;
    }
    EnRr_InitBodySegments(this, globalCtx);
}

void EnRr_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRr* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

void EnRr_SetSpeed(EnRr* this, f32 speed) {
    this->actor.speedXZ = speed;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_WALK);
}

void EnRr_SetupReach(EnRr* this) {
    static f32 segmentHeights[] = { 0.0f, 500.0f, 750.0f, 1000.0f, 1000.0f };
    s32 i;

    this->reachState = 1;
    this->actionTimer = 20;
    this->segPhaseVelTarget = 2500.0f;
    this->segMoveRate = 0.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = segmentHeights[i];
        this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z = 0.8f;
        this->bodySegs[i].rotTarget.x = 6000.0f;
        this->bodySegs[i].rotTarget.z = 0.0f;
    }
    this->actionFunc = EnRr_Reach;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_UNARI);
}

void EnRr_SetupNeutral(EnRr* this) {
    s32 i;

    this->reachState = 0;
    this->segMoveRate = 0.0f;
    this->segPhaseVelTarget = 2500.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = 0.0f;
        this->bodySegs[i].rotTarget.x = this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    if (this->retreat) {
        this->actionTimer = 100;
        this->actionFunc = EnRr_Retreat;
    } else {
        this->actionTimer = 60;
        this->actionFunc = EnRr_Approach;
    }
}

void EnRr_SetupGrabPlayer(EnRr* this, Player* player) {
    s32 i;

    this->grabTimer = 100;
    this->actor.flags &= ~1;
    this->ocTimer = 8;
    this->hasPlayer = true;
    this->reachState = 0;
    this->segMoveRate = this->swallowOffset = this->actor.speedXZ = 0.0f;
    this->pulseSizeTarget = 0.15f;
    this->segPhaseVelTarget = 5000.0f;
    this->wobbleSizeTarget = 512.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = 0.0f;
        this->bodySegs[i].rotTarget.x = this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    this->actionFunc = EnRr_GrabPlayer;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_DRINK);
}

u8 EnRr_GetMessage(u8 shield, u8 tunic) {
    u8 messageIndex = 0;

    if ((shield == PLAYER_SHIELD_DEKU) || (shield == PLAYER_SHIELD_HYLIAN)) {
        messageIndex = RR_MESSAGE_SHIELD;
    }
    if ((tunic == 2 /* Goron tunic */) || (tunic == 3 /* Zora tunic */)) {
        messageIndex |= RR_MESSAGE_TUNIC;
    }

    return messageIndex;
}

void EnRr_SetupReleasePlayer(EnRr* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    u8 shield;
    u8 tunic;

    this->actor.flags |= 1;
    this->hasPlayer = false;
    this->ocTimer = 110;
    this->segMoveRate = 0.0f;
    this->segPhaseVelTarget = 2500.0f;
    this->wobbleSizeTarget = 2048.0f;
    tunic = 0;
    shield = PLAYER_SHIELD_NONE;
    if (CUR_EQUIP_VALUE(EQUIP_SHIELD) != PLAYER_SHIELD_MIRROR) {
        shield = Inventory_DeleteEquipment(globalCtx, EQUIP_SHIELD);
        if (shield != PLAYER_SHIELD_NONE) {
            this->eatenShield = shield;
            this->retreat = true;
        }
    }
    if (CUR_EQUIP_VALUE(EQUIP_TUNIC) != 1 /* Kokiri tunic*/) {
        tunic = Inventory_DeleteEquipment(globalCtx, EQUIP_TUNIC);
        if (tunic != 0) {
            this->eatenTunic = tunic;
            this->retreat = true;
        }
    }
    player->actor.parent = NULL;
    switch (EnRr_GetMessage(shield, tunic)) {
        case RR_MESSAGE_SHIELD:
            func_8010B680(globalCtx, 0x305F, NULL);
            break;
        case RR_MESSAGE_TUNIC:
            func_8010B680(globalCtx, 0x3060, NULL);
            break;
        case RR_MESSAGE_TUNIC | RR_MESSAGE_SHIELD:
            func_8010B680(globalCtx, 0x3061, NULL);
            break;
    }
    osSyncPrintf(VT_FGCOL(YELLOW) "%s[%d] : Rr_Catch_Cancel" VT_RST "\n", "../z_en_rr.c", 650);
    func_8002F6D4(globalCtx, &this->actor, 4.0f, this->actor.shape.rot.y, 12.0f, 8);
    if (this->actor.dmgEffectTimer == 0) {
        this->actionFunc = EnRr_Approach;
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_THROW);
    } else if (this->actor.colChkInfo.health != 0) {
        EnRr_SetupDamage(this);
    } else {
        EnRr_SetupDeath(this);
    }
}

void EnRr_SetupDamage(EnRr* this) {
    s32 i;

    this->reachState = 0;
    this->actionTimer = 20;
    this->segMoveRate = 0.0f;
    this->segPhaseVelTarget = 2500.0f;
    this->pulseSizeTarget = 0.0f;
    this->wobbleSizeTarget = 0.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = 0.0f;
        this->bodySegs[i].rotTarget.x = this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    this->actionFunc = EnRr_Damage;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_DAMAGE);
}

void EnRr_SetupApproach(EnRr* this) {
    s32 i;

    this->segMoveRate = 0.0f;
    this->pulseSizeTarget = 0.15f;
    this->segPhaseVelTarget = 2500.0f;
    this->wobbleSizeTarget = 2048.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = 0.0f;
        this->bodySegs[i].rotTarget.x = this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    this->actionFunc = EnRr_Approach;
}

void EnRr_SetupDeath(EnRr* this) {
    s32 i;

    this->isDead = true;
    this->frameCount = 0;
    this->shrinkRate = 0.0f;
    this->segMoveRate = 0.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].heightTarget = 0.0f;
        this->bodySegs[i].rotTarget.x = this->bodySegs[i].rotTarget.z = 0.0f;
    }
    this->actionFunc = EnRr_Death;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_DEAD);
    this->actor.flags &= ~1;
}

void EnRr_SetupStunned(EnRr* this) {
    s32 i;

    this->stopScroll = true;
    this->segMovePhase = 0;
    this->segPhaseVel = 0.0f;
    this->segPhaseVelTarget = 2500.0f;
    this->segPulsePhaseDiff = 0.0f;
    this->segWobblePhaseDiffX = 0.0f;
    this->segWobbleXTarget = 3.0f;
    this->segWobblePhaseDiffZ = 0.0f;
    this->segWobbleZTarget = 1.0f;
    this->pulseSize = 0.0f;
    this->pulseSizeTarget = 0.15f;
    this->wobbleSize = 0.0f;
    this->wobbleSizeTarget = 2048.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].scaleMod.y = 0.0f;
        this->bodySegs[i].rotTarget.x = 0.0f;
        this->bodySegs[i].rotTarget.y = 0.0f;
        this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scale.x = this->bodySegs[i].scale.y = this->bodySegs[i].scale.z =
            this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.y = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    this->actionFunc = EnRr_Stunned;
}

void EnRr_CollisionCheck(EnRr* this, GlobalContext* globalCtx) {
    Vec3f hitPos;
    Player* player = PLAYER;

    if (this->collider2.base.acFlags & 2) {
        this->collider2.base.acFlags &= ~2;
        // Kakin (not sure what this means)
        osSyncPrintf(VT_FGCOL(GREEN) "カキン(%d)！！" VT_RST "\n", this->frameCount);
        hitPos.x = this->collider2.body.bumper.unk_06.x;
        hitPos.y = this->collider2.body.bumper.unk_06.y;
        hitPos.z = this->collider2.body.bumper.unk_06.z;
        func_80062DF4(globalCtx, &hitPos);
    } else {
        if (this->collider1.base.acFlags & 2) {
            u8 dropType = RR_DROP_RANDOM_RUPEE;

            this->collider1.base.acFlags &= ~2;
            if (this->actor.colChkInfo.damageEffect != 0) {
                hitPos.x = this->collider1.body.bumper.unk_06.x;
                hitPos.y = this->collider1.body.bumper.unk_06.y;
                hitPos.z = this->collider1.body.bumper.unk_06.z;
                func_8005DFAC(globalCtx, NULL, &hitPos);
            }
            switch (this->actor.colChkInfo.damageEffect) {
                case RR_DAMAGE_LIGHT_ARROW:
                    dropType++; // purple rupee
                case RR_DAMAGE_UNK_ARROW_1:
                    dropType++; // flexible
                case RR_DAMAGE_UNK_ARROW_2:
                    dropType++; // arrow
                case RR_DAMAGE_UNK_ARROW_3:
                    dropType++; // magic jar
                case RR_DAMAGE_NORMAL:
                    // ouch
                    osSyncPrintf(VT_FGCOL(RED) "いてっ( %d : LIFE %d : DAMAGE %d : %x )！！" VT_RST "\n",
                                 this->frameCount, this->actor.colChkInfo.health, this->actor.colChkInfo.damage,
                                 this->actor.colChkInfo.damageEffect);
                    this->stopScroll = false;
                    Actor_ApplyDamage(&this->actor);
                    this->invincibilityTimer = 40;
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, this->invincibilityTimer);
                    if (this->hasPlayer) {
                        EnRr_SetupReleasePlayer(this, globalCtx);
                    } else if (this->actor.colChkInfo.health != 0) {
                        EnRr_SetupDamage(this);
                    } else {
                        this->dropType = dropType;
                        EnRr_SetupDeath(this);
                    }
                    return;
                case RR_DAMAGE_FIRE: // Fire Arrow and Din's Fire
                    Actor_ApplyDamage(&this->actor);
                    if (this->actor.colChkInfo.health == 0) {
                        this->dropType = RR_DROP_RANDOM_RUPEE;
                    }
                    func_8003426C(&this->actor, 0x4000, 0xFF, 0x2000, 0x50);
                    this->effectTimer = 20;
                    EnRr_SetupStunned(this);
                    return;
                case RR_DAMAGE_ICE: // Ice Arrow and unused ice magic
                    Actor_ApplyDamage(&this->actor);
                    if (this->actor.colChkInfo.health == 0) {
                        this->dropType = RR_DROP_RANDOM_RUPEE;
                    }
                    if (this->actor.dmgEffectTimer == 0) {
                        this->effectTimer = 20;
                        func_8003426C(&this->actor, 0, 0xFF, 0x2000, 0x50);
                    }
                    EnRr_SetupStunned(this);
                    return;
                case RR_DAMAGE_LIGHT_MAGIC: // Unused light magic
                    Actor_ApplyDamage(&this->actor);
                    if (this->actor.colChkInfo.health == 0) {
                        this->dropType = RR_DROP_RUPEE_RED;
                    }
                    func_8003426C(&this->actor, -0x8000, 0xFF, 0x2000, 0x50);
                    EnRr_SetupStunned(this);
                    return;
                case RR_DAMAGE_STUN: // Boomerang and Hookshot
                    Audio_PlayActorSound2(&this->actor, NA_SE_EN_GOMA_JR_FREEZE);
                    func_8003426C(&this->actor, 0, 0xFF, 0x2000, 0x50);
                    EnRr_SetupStunned(this);
                    return;
            }
        }
        if ((this->ocTimer == 0) && (this->actor.dmgEffectTimer == 0) && (player->invincibilityTimer == 0) &&
            !(player->stateFlags2 & 0x80) && ((this->collider1.base.maskA & 2) || (this->collider2.base.maskA & 2))) {
            this->collider1.base.maskA &= ~2;
            this->collider2.base.maskA &= ~2;
            // catch
            osSyncPrintf(VT_FGCOL(GREEN) "キャッチ(%d)！！" VT_RST "\n", this->frameCount);
            if (globalCtx->grabPlayer(globalCtx, player)) {
                player->actor.parent = &this->actor;
                this->stopScroll = false;
                EnRr_SetupGrabPlayer(this, player);
            }
        }
    }
}

void EnRr_InitBodySegments(EnRr* this, GlobalContext* globalCtx) {
    s32 i;

    this->segMovePhase = 0;
    this->segPhaseVel = 0.0f;
    this->segPhaseVelTarget = 2500.0f;
    this->segPulsePhaseDiff = 0.0f;
    this->segWobblePhaseDiffX = 0.0f;
    this->segWobbleXTarget = 3.0f;
    this->segWobblePhaseDiffZ = 0.0f;
    this->segWobbleZTarget = 1.0f;
    this->pulseSize = 0.0f;
    this->pulseSizeTarget = 0.15f;
    this->wobbleSize = 0.0f;
    this->wobbleSizeTarget = 2048.0f;
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].scaleMod.y = 0.0f;
        this->bodySegs[i].rotTarget.x = 0.0f;
        this->bodySegs[i].rotTarget.y = 0.0f;
        this->bodySegs[i].rotTarget.z = 0.0f;
        this->bodySegs[i].scale.x = this->bodySegs[i].scale.y = this->bodySegs[i].scale.z =
            this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.y = this->bodySegs[i].scaleTarget.z = 1.0f;
    }
    for (i = 0; i < 5; i++) {
        this->bodySegs[i].scaleMod.x = this->bodySegs[i].scaleMod.z =
            Math_Coss(i * (u32)(s16)this->segPulsePhaseDiff * 0x1000) * this->pulseSize;
    }
    for (i = 1; i < 5; i++) {
        this->bodySegs[i].rotTarget.x = Math_Coss(i * (u32)(s16)this->segWobblePhaseDiffX * 0x1000) * this->wobbleSize;
        this->bodySegs[i].rotTarget.z = Math_Sins(i * (u32)(s16)this->segWobblePhaseDiffZ * 0x1000) * this->wobbleSize;
    }
}

void EnRr_UpdateBodySegments(EnRr* this, GlobalContext* globalCtx) {
    s32 i;
    s16 phase = this->segMovePhase;

    if (!this->isDead) {
        for (i = 0; i < 5; i++) {
            this->bodySegs[i].scaleMod.x = this->bodySegs[i].scaleMod.z =
                Math_Coss(phase + i * (s16)this->segPulsePhaseDiff * 0x1000) * this->pulseSize;
        }
        phase = this->segMovePhase;
        if (!this->isDead && (this->reachState == 0)) {
            for (i = 1; i < 5; i++) {
                this->bodySegs[i].rotTarget.x =
                    Math_Coss(phase + i * (s16)this->segWobblePhaseDiffX * 0x1000) * this->wobbleSize;
                this->bodySegs[i].rotTarget.z =
                    Math_Sins(phase + i * (s16)this->segWobblePhaseDiffZ * 0x1000) * this->wobbleSize;
            }
        }
    }
    if (!this->stopScroll) {
        this->segMovePhase += (s16)this->segPhaseVel;
    }
}

void EnRr_Approach(EnRr* this, GlobalContext* globalCtx) {
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 0xA, 0x1F4, 0);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    if ((this->actionTimer == 0) && (this->actor.xzDistFromLink < 160.0f)) {
        EnRr_SetupReach(this);
    } else if ((this->actor.xzDistFromLink < 400.0f) && (this->actor.speedXZ == 0.0f)) {
        EnRr_SetSpeed(this, 2.0f);
    }
}

void EnRr_Reach(EnRr* this, GlobalContext* globalCtx) {
    Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink, 0xA, 0x1F4, 0);
    this->actor.posRot.rot.y = this->actor.shape.rot.y;
    switch (this->reachState) {
        case REACH_EXTEND:
            if (this->actionTimer == 0) {
                this->reachState = REACH_STOP;
            }
            break;
        case REACH_STOP:
            if (this->actionTimer == 0) {
                this->actionTimer = 5;
                this->bodySegs[RR_MOUTH].scaleTarget.x = this->bodySegs[RR_MOUTH].scaleTarget.z = 1.5f;
                this->reachState = REACH_OPEN;
            }
            break;
        case REACH_OPEN:
            if (this->actionTimer == 0) {
                this->actionTimer = 2;
                this->bodySegs[RR_MOUTH].heightTarget = 2000.0f;
                this->reachState = REACH_GAPE;
            }
            break;
        case REACH_GAPE:
            if (this->actionTimer == 0) {
                this->actionTimer = 20;
                this->bodySegs[RR_MOUTH].scaleTarget.x = this->bodySegs[RR_MOUTH].scaleTarget.z = 0.8f;
                this->reachState = REACH_CLOSE;
            }
            break;
        case REACH_CLOSE:
            if (this->actionTimer == 0) {
                EnRr_SetupNeutral(this);
            }
            break;
    }
}

void EnRr_GrabPlayer(EnRr* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    func_800AA000(this->actor.xyzDistFromLinkSq, 120, 2, 120);
    if ((this->frameCount % 8) == 0) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_LIKE_EAT);
    }
    this->ocTimer = 8;
    if ((this->grabTimer == 0) || !(player->stateFlags2 & 0x80)) {
        EnRr_SetupReleasePlayer(this, globalCtx);
    } else {
        Math_SmoothScaleMaxF(&player->actor.posRot.pos.x, this->mouthPos.x, 1.0f, 30.0f);
        Math_SmoothScaleMaxF(&player->actor.posRot.pos.y, this->mouthPos.y + this->swallowOffset, 1.0f, 30.0f);
        Math_SmoothScaleMaxF(&player->actor.posRot.pos.z, this->mouthPos.z, 1.0f, 30.0f);
        Math_SmoothScaleMaxF(&this->swallowOffset, -55.0f, 1.0f, 5.0f);
    }
}

void EnRr_Damage(EnRr* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->actor.dmgEffectTimer == 0) {
        EnRr_SetupApproach(this);
    } else if ((this->actor.dmgEffectTimer & 8) != 0) {
        for (i = 1; i < 5; i++) {
            this->bodySegs[i].rotTarget.z = 5000.0f;
        }
    } else {
        for (i = 1; i < 5; i++) {
            this->bodySegs[i].rotTarget.z = -5000.0f;
        }
    }
}

void EnRr_Death(EnRr* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 i;

    if (this->frameCount < 40) {
        for (i = 0; i < 5; i++) {
            Math_SmoothScaleMaxF(&this->bodySegs[i].heightTarget, i + 59 - (this->frameCount * 25.0f), 1.0f, 50.0f);
            this->bodySegs[i].scaleTarget.x = this->bodySegs[i].scaleTarget.z =
                (SQ(4 - i) * (f32)this->frameCount * 0.003f) + 1.0f;
        }
    } else if (this->frameCount >= 95) {
        Vec3f dropPos;

        dropPos.x = this->actor.posRot.pos.x;
        dropPos.y = this->actor.posRot.pos.y;
        dropPos.z = this->actor.posRot.pos.z;
        switch (this->eatenShield) {
            case PLAYER_SHIELD_DEKU:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_SHIELD_DEKU);
                break;
            case PLAYER_SHIELD_HYLIAN:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_SHIELD_HYLIAN);
                break;
        }
        switch (this->eatenTunic) {
            case PLAYER_TUNIC_GORON + 1:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_TUNIC_GORON);
                break;
            case PLAYER_TUNIC_ZORA + 1:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_TUNIC_ZORA);
                break;
        }
        // dropped
        osSyncPrintf(VT_FGCOL(GREEN) "「%s」が出た！！" VT_RST "\n", sDropNames[this->dropType]);
        switch (this->dropType) {
            case RR_DROP_MAGIC:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_MAGIC_SMALL);
                break;
            case RR_DROP_ARROW:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_ARROWS_SINGLE);
                break;
            case RR_DROP_FLEXIBLE:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_FLEXIBLE);
                break;
            case RR_DROP_RUPEE_PURPLE:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_RUPEE_PURPLE);
                break;
            case RR_DROP_RUPEE_RED:
                Item_DropCollectible(globalCtx, &dropPos, ITEM00_RUPEE_RED);
                break;
            case RR_DROP_RANDOM_RUPEE:
            default:
                Item_DropCollectibleRandom(globalCtx, &this->actor, &dropPos, 12 << 4);
                break;
        }
        Actor_Kill(&this->actor);
    } else if (this->frameCount == 88) {
        Vec3f pos;
        Vec3f vel;
        Vec3f accel;

        pos.x = this->actor.posRot.pos.x;
        pos.y = this->actor.posRot.pos.y + 20.0f;
        pos.z = this->actor.posRot.pos.z;
        vel.x = 0.0f;
        vel.y = 0.0f;
        vel.z = 0.0f;
        accel.x = 0.0f;
        accel.y = 0.0f;
        accel.z = 0.0f;

        EffectSsDeadDb_Spawn(globalCtx, &pos, &vel, &accel, 100, 0, 255, 255, 255, 255, 255, 0, 0, 1, 9, true);
    } else {
        Math_SmoothScaleMaxF(&this->actor.scale.x, 0.0f, 1.0f, this->shrinkRate);
        Math_SmoothScaleMaxF(&this->shrinkRate, 0.001f, 1.0f, 0.00001f);
        this->actor.scale.z = this->actor.scale.x;
    }
}

void EnRr_Retreat(EnRr* this, GlobalContext* globalCtx) {
    if (this->actionTimer == 0) {
        this->retreat = false;
        this->actionFunc = EnRr_Approach;
    } else {
        Math_SmoothScaleMaxMinS(&this->actor.shape.rot.y, this->actor.yawTowardsLink + 0x8000, 0xA, 0x3E8, 0);
        this->actor.posRot.rot.y = this->actor.shape.rot.y;
        if (this->actor.speedXZ == 0.0f) {
            EnRr_SetSpeed(this, 2.0f);
        }
    }
}

void EnRr_Stunned(EnRr* this, GlobalContext* globalCtx) {
    if (this->actor.dmgEffectTimer == 0) {
        this->stopScroll = false;
        if (this->hasPlayer) {
            EnRr_SetupReleasePlayer(this, globalCtx);
        } else if (this->actor.colChkInfo.health != 0) {
            this->actionFunc = EnRr_Approach;
        } else {
            EnRr_SetupDeath(this);
        }
    }
}

void EnRr_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRr* this = THIS;
    s32 i;

    this->frameCount++;
    if (!this->stopScroll) {
        this->scrollTimer++;
    }
    if (this->actionTimer != 0) {
        this->actionTimer--;
    }
    if (this->grabTimer != 0) {
        this->grabTimer--;
    }
    if (this->ocTimer != 0) {
        this->ocTimer--;
    }
    if (this->invincibilityTimer != 0) {
        this->invincibilityTimer--;
    }
    if (this->effectTimer != 0) {
        this->effectTimer--;
    }

    Actor_SetHeight(&this->actor, 30.0f);
    EnRr_UpdateBodySegments(this, globalCtx);
    if (!this->isDead && ((this->actor.dmgEffectTimer == 0) || !(this->actor.dmgEffectParams & 0x4000))) {
        EnRr_CollisionCheck(this, globalCtx);
    }

    this->actionFunc(this, globalCtx);
    if (this->hasPlayer == 0x3F80) { // checks if 1.0f has been stored to hasPlayer's address
        __assert("0", "../z_en_rr.c", 1355);
    }

    Math_ApproxF(&this->actor.speedXZ, 0.0f, 0.1f);
    Actor_MoveForward(&this->actor);
    Collider_CylinderUpdate(&this->actor, &this->collider1);
    this->collider2.dim.pos.x = this->mouthPos.x;
    this->collider2.dim.pos.y = this->mouthPos.y;
    this->collider2.dim.pos.z = this->mouthPos.z;
    if (!this->isDead && (this->invincibilityTimer == 0)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        if (this->ocTimer == 0) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    } else {
        this->collider2.base.maskA &= ~2;
        this->collider2.base.acFlags &= ~2;
        this->collider1.base.maskA &= ~2;
        this->collider1.base.acFlags &= ~2;
    }
    func_8002E4B4(globalCtx, &this->actor, 20.0f, 30.0f, 20.0f, 7);
    if (!this->stopScroll) {
        Math_SmoothScaleMaxF(&this->segPhaseVel, this->segPhaseVelTarget, 1.0f, 50.0f);
        Math_SmoothScaleMaxF(&this->segPulsePhaseDiff, 4.0f, 1.0f, 5.0f);
        Math_SmoothScaleMaxF(&this->segWobblePhaseDiffX, this->segWobbleXTarget, 1.0f, 0.04f);
        Math_SmoothScaleMaxF(&this->segWobblePhaseDiffZ, this->segWobbleZTarget, 1.0f, 0.01f);
        Math_SmoothScaleMaxF(&this->pulseSize, this->pulseSizeTarget, 1.0f, 0.0015f);
        Math_SmoothScaleMaxF(&this->wobbleSize, this->wobbleSizeTarget, 1.0f, 20.0f);
        for (i = 0; i < 5; i++) {
            Math_SmoothScaleMaxMinS(&this->bodySegs[i].rot.x, this->bodySegs[i].rotTarget.x, 5,
                                    this->segMoveRate * 1000.0f, 0);
            Math_SmoothScaleMaxMinS(&this->bodySegs[i].rot.z, this->bodySegs[i].rotTarget.z, 5,
                                    this->segMoveRate * 1000.0f, 0);
            Math_SmoothScaleMaxF(&this->bodySegs[i].scale.x, this->bodySegs[i].scaleTarget.x, 1.0f,
                                 this->segMoveRate * 0.2f);
            this->bodySegs[i].scale.z = this->bodySegs[i].scale.x;
            Math_SmoothScaleMaxF(&this->bodySegs[i].height, this->bodySegs[i].heightTarget, 1.0f,
                                 this->segMoveRate * 300.0f);
        }
        Math_SmoothScaleMaxF(&this->segMoveRate, 1.0f, 1.0f, 0.2f);
    }
}

static Vec3f sEffectOffsets[] = {
    { 25.0f, 0.0f, 0.0f },
    { -25.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 25.0f },
    { 0.0f, 0.0f, -25.0f },
};

void EnRr_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f zeroVec;
    EnRr* this = THIS;
    s32 i;
    Mtx* segMtx = Graph_Alloc(globalCtx->state.gfxCtx, 4 * sizeof(Mtx));

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_en_rr.c", 1478);
    if (1) {}
    func_80093D84(globalCtx->state.gfxCtx);
    gSPSegment(POLY_XLU_DISP++, 0x0C, segMtx);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (this->scrollTimer * 0) & 0x7F,
                                (this->scrollTimer * 0) & 0x3F, 32, 16, 1, (this->scrollTimer * 0) & 0x3F,
                                (this->scrollTimer * -6) & 0x7F, 32, 16));
    Matrix_Push();

    Matrix_Scale((1.0f + this->bodySegs[RR_BASE].scaleMod.x) * this->bodySegs[RR_BASE].scale.x,
                 (1.0f + this->bodySegs[RR_BASE].scaleMod.y) * this->bodySegs[RR_BASE].scale.y,
                 (1.0f + this->bodySegs[RR_BASE].scaleMod.z) * this->bodySegs[RR_BASE].scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_en_rr.c", 1501),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Matrix_Pull();
    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    for (i = 1; i < 5; i++) {
        Matrix_Translate(0.0f, this->bodySegs[i].height + 1000.0f, 0.0f, MTXMODE_APPLY);

        Matrix_RotateRPY(this->bodySegs[i].rot.x, this->bodySegs[i].rot.y, this->bodySegs[i].rot.z, MTXMODE_APPLY);
        Matrix_Push();
        Matrix_Scale((1.0f + this->bodySegs[i].scaleMod.x) * this->bodySegs[i].scale.x,
                     (1.0f + this->bodySegs[i].scaleMod.y) * this->bodySegs[i].scale.y,
                     (1.0f + this->bodySegs[i].scaleMod.z) * this->bodySegs[i].scale.z, MTXMODE_APPLY);
        Matrix_ToMtx(segMtx, "../z_en_rr.c", 1527);
        Matrix_Pull();
        segMtx++;
        Matrix_MultVec3f(&zeroVec, &this->effectPos[i]);
    }
    this->effectPos[0] = this->actor.posRot.pos;
    Matrix_MultVec3f(&zeroVec, &this->mouthPos);
    gSPDisplayList(POLY_XLU_DISP++, D_06000470);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_en_rr.c", 1551);
    if (this->effectTimer != 0) {
        Vec3f effectPos;
        s16 effectTimer = this->effectTimer - 1;

        this->actor.dmgEffectTimer++;
        if ((effectTimer & 1) == 0) {
            s32 segIndex = 4 - (effectTimer >> 2);
            s32 offIndex = (effectTimer >> 1) & 3;

            effectPos.x = this->effectPos[segIndex].x + sEffectOffsets[offIndex].x + Math_Rand_CenteredFloat(10.0f);
            effectPos.y = this->effectPos[segIndex].y + sEffectOffsets[offIndex].y + Math_Rand_CenteredFloat(10.0f);
            effectPos.z = this->effectPos[segIndex].z + sEffectOffsets[offIndex].z + Math_Rand_CenteredFloat(10.0f);
            if (this->actor.dmgEffectParams & 0x4000) {
                EffectSsEnFire_SpawnVec3f(globalCtx, &this->actor, &effectPos, 100, 0, 0, -1);
            } else {
                EffectSsEnIce_SpawnFlyingVec3f(globalCtx, &this->actor, &effectPos, 150, 150, 150, 250, 235, 245, 255,
                                               3.0f);
            }
        }
    }
}
