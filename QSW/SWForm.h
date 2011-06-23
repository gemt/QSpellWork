#ifndef SWFORM_H
#define SWFORM_H

#include <QtGui/QMainWindow>
#include <QtGui/QToolButton>
#include <QtGui/QPixmap>
#include <QtGui/QIcon>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebFrame>
#include "SWObject.h"
#include "ui_SWFormUI.h"

class SWObject;
class SpellListSortedModel;

class SWForm : public QMainWindow, public Ui::SWFormUI
{
    Q_OBJECT

    public:
        SWForm(QWidget* parent = 0);
        ~SWForm();

        QWebView* getBrowser(quint8 num) { return(num == 0 ? webView : webView_2); }

    signals:
        void signalSearch(quint8 type);

    private slots:
        void slotAbout();
        void slotFilterSearch();
        void slotButtonSearch();
        void slotCompareSearch();
        void slotSetMode(QAction* ac);
        void slotSearch(quint8 type);
        void slotSearchFromList(const QModelIndex &index);
        void slotLinkClicked(const QUrl &url);
        void slotRegExp();

        bool event(QEvent* ev);

    private:
        void loadComboBoxes();
        void detectLocale();
        void createModeButton();

        SpellListSortedModel* m_sortedModel;
        Ui::SWFormUI m_ui;
        SWObject* m_sw;
        QToolButton* m_modeButton;
        QAction* m_regExp;
        QAction* m_about;
};

class Enums : public QObject
{
    Q_OBJECT
public:

    enum LocalesDBC
    {
        enUS,
        koKR,
        frFR,
        deDE,
        zhCN,
        zhTW,
        esES,
        esMX
    };

    enum Mechanic
    {
        MECHANIC_NONE,
        MECHANIC_CHARM,
        MECHANIC_DISORIENTED,
        MECHANIC_DISARM,
        MECHANIC_DISTRACT,
        MECHANIC_FEAR,
        MECHANIC_FUMBLE,
        MECHANIC_ROOT,
        MECHANIC_PACIFY,
        MECHANIC_SILENCE,
        MECHANIC_SLEEP,
        MECHANIC_SNARE,
        MECHANIC_STUN,
        MECHANIC_FREEZE,
        MECHANIC_KNOCKOUT,
        MECHANIC_BLEED,
        MECHANIC_BANDAGE,
        MECHANIC_POLYMORPH,
        MECHANIC_BANISH,
        MECHANIC_SHIELD,
        MECHANIC_SHACKLE,
        MECHANIC_MOUNT,
        MECHANIC_PERSUADE,
        MECHANIC_TURN,
        MECHANIC_HORROR,
        MECHANIC_INVULNERABILITY,
        MECHANIC_INTERRUPT,
        MECHANIC_DAZE,
        MECHANIC_DISCOVERY,
        MECHANIC_IMMUNE_SHIELD,
        MECHANIC_SAPPED
    };

    enum PreventionType
    {
        SPELL_PREVENTION_TYPE_NONE,
        SPELL_PREVENTION_TYPE_SILENCE,
        SPELL_PREVENTION_TYPE_PACIFY
    };

    enum DamageClass
    {
        SPELL_DAMAGE_CLASS_NONE,
        SPELL_DAMAGE_CLASS_MAGIC,
        SPELL_DAMAGE_CLASS_MELEE,
        SPELL_DAMAGE_CLASS_RANGED
    };

    enum School
    {
        SPELL_SCHOOL_NORMAL,
        SPELL_SCHOOL_HOLY,
        SPELL_SCHOOL_FIRE,
        SPELL_SCHOOL_NATURE,
        SPELL_SCHOOL_FROST,
        SPELL_SCHOOL_SHADOW,
        SPELL_SCHOOL_ARCANE
    };

    enum Effects
    {
        SPELL_EFFECT_NONE,
        SPELL_EFFECT_INSTAKILL,
        SPELL_EFFECT_SCHOOL_DAMAGE,
        SPELL_EFFECT_DUMMY,
        SPELL_EFFECT_PORTAL_TELEPORT,
        SPELL_EFFECT_TELEPORT_UNITS,
        SPELL_EFFECT_APPLY_AURA,
        SPELL_EFFECT_ENVIRONMENTAL_DAMAGE,
        SPELL_EFFECT_POWER_DRAIN,
        SPELL_EFFECT_HEALTH_LEECH,
        SPELL_EFFECT_HEAL,
        SPELL_EFFECT_BIND,
        SPELL_EFFECT_PORTAL,
        SPELL_EFFECT_RITUAL_BASE,
        SPELL_EFFECT_RITUAL_SPECIALIZE,
        SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL,
        SPELL_EFFECT_QUEST_COMPLETE,
        SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL,
        SPELL_EFFECT_RESURRECT,
        SPELL_EFFECT_ADD_EXTRA_ATTACKS,
        SPELL_EFFECT_DODGE,
        SPELL_EFFECT_EVADE,
        SPELL_EFFECT_PARRY,
        SPELL_EFFECT_BLOCK,
        SPELL_EFFECT_CREATE_ITEM,
        SPELL_EFFECT_WEAPON,
        SPELL_EFFECT_DEFENSE,
        SPELL_EFFECT_PERSISTENT_AREA_AURA,
        SPELL_EFFECT_SUMMON,
        SPELL_EFFECT_LEAP,
        SPELL_EFFECT_ENERGIZE,
        SPELL_EFFECT_WEAPON_PERCENT_DAMAGE,
        SPELL_EFFECT_TRIGGER_MISSILE,
        SPELL_EFFECT_OPEN_LOCK,
        SPELL_EFFECT_SUMMON_CHANGE_ITEM,
        SPELL_EFFECT_APPLY_AREA_AURA_PARTY,
        SPELL_EFFECT_LEARN_SPELL,
        SPELL_EFFECT_SPELL_DEFENSE,
        SPELL_EFFECT_DISPEL,
        SPELL_EFFECT_LANGUAGE,
        SPELL_EFFECT_DUAL_WIELD,
        SPELL_EFFECT_SUMMON_WILD,
        SPELL_EFFECT_SUMMON_GUARDIAN,
        SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER,
        SPELL_EFFECT_SKILL_STEP,
        SPELL_EFFECT_ADD_HONOR,
        SPELL_EFFECT_SPAWN,
        SPELL_EFFECT_TRADE_SKILL,
        SPELL_EFFECT_STEALTH,
        SPELL_EFFECT_DETECT,
        SPELL_EFFECT_TRANS_DOOR,
        SPELL_EFFECT_FORCE_CRITICAL_HIT,
        SPELL_EFFECT_GUARANTEE_HIT,
        SPELL_EFFECT_ENCHANT_ITEM,
        SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY,
        SPELL_EFFECT_TAMECREATURE,
        SPELL_EFFECT_SUMMON_PET,
        SPELL_EFFECT_LEARN_PET_SPELL,
        SPELL_EFFECT_WEAPON_DAMAGE,
        SPELL_EFFECT_OPEN_LOCK_ITEM,
        SPELL_EFFECT_PROFICIENCY,
        SPELL_EFFECT_SEND_EVENT,
        SPELL_EFFECT_POWER_BURN,
        SPELL_EFFECT_THREAT,
        SPELL_EFFECT_TRIGGER_SPELL,
        SPELL_EFFECT_HEALTH_FUNNEL,
        SPELL_EFFECT_POWER_FUNNEL,
        SPELL_EFFECT_HEAL_MAX_HEALTH,
        SPELL_EFFECT_INTERRUPT_CAST,
        SPELL_EFFECT_DISTRACT,
        SPELL_EFFECT_PULL,
        SPELL_EFFECT_PICKPOCKET,
        SPELL_EFFECT_ADD_FARSIGHT,
        SPELL_EFFECT_SUMMON_POSSESSED,
        SPELL_EFFECT_SUMMON_TOTEM,
        SPELL_EFFECT_HEAL_MECHANICAL,
        SPELL_EFFECT_SUMMON_OBJECT_WILD,
        SPELL_EFFECT_SCRIPT_EFFECT,
        SPELL_EFFECT_ATTACK,
        SPELL_EFFECT_SANCTUARY,
        SPELL_EFFECT_ADD_COMBO_POINTS,
        SPELL_EFFECT_CREATE_HOUSE,
        SPELL_EFFECT_BIND_SIGHT,
        SPELL_EFFECT_DUEL,
        SPELL_EFFECT_STUCK,
        SPELL_EFFECT_SUMMON_PLAYER,
        SPELL_EFFECT_ACTIVATE_OBJECT,
        SPELL_EFFECT_SUMMON_TOTEM_SLOT1,
        SPELL_EFFECT_SUMMON_TOTEM_SLOT2,
        SPELL_EFFECT_SUMMON_TOTEM_SLOT3,
        SPELL_EFFECT_SUMMON_TOTEM_SLOT4,
        SPELL_EFFECT_THREAT_ALL,
        SPELL_EFFECT_ENCHANT_HELD_ITEM,
        SPELL_EFFECT_SUMMON_PHANTASM,
        SPELL_EFFECT_SELF_RESURRECT,
        SPELL_EFFECT_SKINNING,
        SPELL_EFFECT_CHARGE,
        SPELL_EFFECT_SUMMON_CRITTER,
        SPELL_EFFECT_KNOCK_BACK,
        SPELL_EFFECT_DISENCHANT,
        SPELL_EFFECT_INEBRIATE,
        SPELL_EFFECT_FEED_PET,
        SPELL_EFFECT_DISMISS_PET,
        SPELL_EFFECT_REPUTATION,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT1,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT2,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT3,
        SPELL_EFFECT_SUMMON_OBJECT_SLOT4,
        SPELL_EFFECT_DISPEL_MECHANIC,
        SPELL_EFFECT_SUMMON_DEAD_PET,
        SPELL_EFFECT_DESTROY_ALL_TOTEMS,
        SPELL_EFFECT_DURABILITY_DAMAGE,
        SPELL_EFFECT_SUMMON_DEMON,
        SPELL_EFFECT_RESURRECT_NEW,
        SPELL_EFFECT_ATTACK_ME,
        SPELL_EFFECT_DURABILITY_DAMAGE_PCT,
        SPELL_EFFECT_SKIN_PLAYER_CORPSE,
        SPELL_EFFECT_SPIRIT_HEAL,
        SPELL_EFFECT_SKILL,
        SPELL_EFFECT_APPLY_AREA_AURA_PET,
        SPELL_EFFECT_TELEPORT_GRAVEYARD,
        SPELL_EFFECT_NORMALIZED_WEAPON_DMG,
        SPELL_EFFECT_122,
        SPELL_EFFECT_SEND_TAXI,
        SPELL_EFFECT_PLAYER_PULL,
        SPELL_EFFECT_MODIFY_THREAT_PERCENT,
        SPELL_EFFECT_126,
        SPELL_EFFECT_127,
        SPELL_EFFECT_128,
        SPELL_EFFECT_129
    };

    enum TargetFlags
    {
        TARGET_FLAG_SELF            = 0x00,
        TARGET_FLAG_UNUSED1         = 1 << 0x00,
        TARGET_FLAG_UNIT            = 1 << 0x01,
        TARGET_FLAG_UNUSED2         = 1 << 0x02,
        TARGET_FLAG_UNUSED3         = 1 << 0x03,
        TARGET_FLAG_ITEM            = 1 << 0x04,
        TARGET_FLAG_SOURCE_LOCATION = 1 << 0x05,
        TARGET_FLAG_DEST_LOCATION   = 1 << 0x06,
        TARGET_FLAG_OBJECT_UNK      = 1 << 0x07,
        TARGET_FLAG_UNIT_UNK        = 1 << 0x08,
        TARGET_FLAG_PVP_CORPSE      = 1 << 0x09,
        TARGET_FLAG_UNIT_CORPSE     = 1 << 0x0A,
        TARGET_FLAG_OBJECT          = 1 << 0x0B,
        TARGET_FLAG_TRADE_ITEM      = 1 << 0x0C,
        TARGET_FLAG_STRING          = 1 << 0x0D,
        TARGET_FLAG_UNK1            = 1 << 0x0E,
        TARGET_FLAG_CORPSE          = 1 << 0x0F,
        TARGET_FLAG_UNK2            = 1 << 0x10
    };

    enum CreatureTypeMask
    {
        NONE            = 0x0,
        BEAST           = 1 << 0x0,
        DRAGONKIN       = 1 << 0x1,
        DEMON           = 1 << 0x2,
        ELEMENTAL       = 1 << 0x3,
        GIANT           = 1 << 0x4,
        UNDEAD          = 1 << 0x5,
        HUMANOID        = 1 << 0x6,
        CRITTER         = 1 << 0x7,
        MECHANICAL      = 1 << 0x8,
        NOT_SPECIFIED   = 1 << 0x9,
        TOTEM_CREATURE  = 1 << 0xA,
    };

    enum Attributes
    {
        SPELL_ATTR_UNK0                             = 1 << 0x00,
        SPELL_ATTR_RANGED                           = 1 << 0x01,
        SPELL_ATTR_ON_NEXT_SWING_1                  = 1 << 0x02,
        SPELL_ATTR_UNK3                             = 1 << 0x03,
        SPELL_ATTR_UNK4                             = 1 << 0x04,
        SPELL_ATTR_TRADESPELL                       = 1 << 0x05,
        SPELL_ATTR_PASSIVE                          = 1 << 0x06,
        SPELL_ATTR_UNK7                             = 1 << 0x07,
        SPELL_ATTR_UNK8                             = 1 << 0x08,
        SPELL_ATTR_UNK9                             = 1 << 0x09,
        SPELL_ATTR_ON_NEXT_SWING_2                  = 1 << 0x0A,
        SPELL_ATTR_UNK11                            = 1 << 0x0B,
        SPELL_ATTR_DAYTIME_ONLY                     = 1 << 0x0C,
        SPELL_ATTR_NIGHT_ONLY                       = 1 << 0x0D,
        SPELL_ATTR_INDOORS_ONLY                     = 1 << 0x0E,
        SPELL_ATTR_OUTDOORS_ONLY                    = 1 << 0x0F,
        SPELL_ATTR_NOT_SHAPESHIFT                   = 1 << 0x10,
        SPELL_ATTR_ONLY_STEALTHED                   = 1 << 0x11,
        SPELL_ATTR_UNK18                            = 1 << 0x12,
        SPELL_ATTR_LEVEL_DAMAGE_CALCULATION         = 1 << 0x13,
        SPELL_ATTR_STOP_ATTACK_TARGET               = 1 << 0x14,
        SPELL_ATTR_IMPOSSIBLE_DODGE_PARRY_BLOCK     = 1 << 0x15,
        SPELL_ATTR_UNK22                            = 1 << 0x16,
        SPELL_ATTR_UNK23                            = 1 << 0x17,
        SPELL_ATTR_CASTABLE_WHILE_MOUNTED           = 1 << 0x18,
        SPELL_ATTR_DISABLED_WHILE_ACTIVE            = 1 << 0x19,
        SPELL_ATTR_UNK26                            = 1 << 0x1A,
        SPELL_ATTR_CASTABLE_WHILE_SITTING           = 1 << 0x1B,
        SPELL_ATTR_CANT_USED_IN_COMBAT              = 1 << 0x1C,
        SPELL_ATTR_UNAFFECTED_BY_INVULNERABILITY    = 1 << 0x1D,
        SPELL_ATTR_UNK30                            = 1 << 0x1E,
        SPELL_ATTR_CANT_CANCEL                      = 1 << 0x1F
    };

    enum AttributesEx
    {
        SPELL_ATTR_EX_UNK0                          = 1 << 0x00,
        SPELL_ATTR_EX_DRAIN_ALL_POWER               = 1 << 0x01,
        SPELL_ATTR_EX_CHANNELED_1                   = 1 << 0x02,
        SPELL_ATTR_EX_UNK3                          = 1 << 0x03,
        SPELL_ATTR_EX_UNK4                          = 1 << 0x04,
        SPELL_ATTR_EX_NOT_BREAK_STEALTH             = 1 << 0x05,
        SPELL_ATTR_EX_CHANNELED_2                   = 1 << 0x06,
        SPELL_ATTR_EX_NEGATIVE                      = 1 << 0x07,
        SPELL_ATTR_EX_NOT_IN_COMBAT_TARGET          = 1 << 0x08,
        SPELL_ATTR_EX_UNK9                          = 1 << 0x09,
        SPELL_ATTR_EX_NO_INITIAL_AGGRO              = 1 << 0x0A,
        SPELL_ATTR_EX_UNK11                         = 1 << 0x0B,
        SPELL_ATTR_EX_UNK12                         = 1 << 0x0C,
        SPELL_ATTR_EX_UNK13                         = 1 << 0x0D,
        SPELL_ATTR_EX_UNK14                         = 1 << 0x0E,
        SPELL_ATTR_EX_DISPEL_AURAS_ON_IMMUNITY      = 1 << 0x0F,
        SPELL_ATTR_EX_UNAFFECTED_BY_SCHOOL_IMMUNE   = 1 << 0x10,
        SPELL_ATTR_EX_UNK17                         = 1 << 0x11,
        SPELL_ATTR_EX_UNK18                         = 1 << 0x12,
        SPELL_ATTR_EX_UNK19                         = 1 << 0x13,
        SPELL_ATTR_EX_REQ_TARGET_COMBO_POINTS       = 1 << 0x14,
        SPELL_ATTR_EX_UNK21                         = 1 << 0x15,
        SPELL_ATTR_EX_REQ_COMBO_POINTS              = 1 << 0x16,
        SPELL_ATTR_EX_UNK23                         = 1 << 0x17,
        SPELL_ATTR_EX_UNK24                         = 1 << 0x18,
        SPELL_ATTR_EX_UNK25                         = 1 << 0x19,
        SPELL_ATTR_EX_UNK26                         = 1 << 0x1A,
        SPELL_ATTR_EX_UNK27                         = 1 << 0x1B,
        SPELL_ATTR_EX_UNK28                         = 1 << 0x1C,
        SPELL_ATTR_EX_UNK29                         = 1 << 0x1D,
        SPELL_ATTR_EX_UNK30                         = 1 << 0x1E,
        SPELL_ATTR_EX_UNK31                         = 1 << 0x1F
    };

    enum AttributesEx2
    {
        SPELL_ATTR_EX2_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX2_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX2_CANT_REFLECTED               = 1 << 0x02,
        SPELL_ATTR_EX2_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX2_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX2_AUTOREPEAT_FLAG              = 1 << 0x05,
        SPELL_ATTR_EX2_UNK6                         = 1 << 0x06,
        SPELL_ATTR_EX2_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX2_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX2_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX2_UNK10                        = 1 << 0x0A,
        SPELL_ATTR_EX2_HEALTH_FUNNEL                = 1 << 0x0B,
        SPELL_ATTR_EX2_UNK12                        = 1 << 0x0C,
        SPELL_ATTR_EX2_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX2_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX2_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX2_UNK16                        = 1 << 0x10,
        SPELL_ATTR_EX2_UNK17                        = 1 << 0x11,
        SPELL_ATTR_EX2_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX2_NOT_NEED_SHAPESHIFT          = 1 << 0x13,
        SPELL_ATTR_EX2_UNK20                        = 1 << 0x14,
        SPELL_ATTR_EX2_DAMAGE_REDUCED_SHIELD        = 1 << 0x15,
        SPELL_ATTR_EX2_UNK22                        = 1 << 0x16,
        SPELL_ATTR_EX2_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX2_UNK24                        = 1 << 0x18,
        SPELL_ATTR_EX2_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX2_UNK26                        = 1 << 0x1A,
        SPELL_ATTR_EX2_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX2_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX2_CANT_CRIT                    = 1 << 0x1D,
        SPELL_ATTR_EX2_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX2_FOOD_BUFF                    = 1 << 0x1F
    };

    enum AttributesEx3
    {
        SPELL_ATTR_EX3_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX3_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX3_UNK2                         = 1 << 0x02,
        SPELL_ATTR_EX3_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX3_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX3_UNK5                         = 1 << 0x05,
        SPELL_ATTR_EX3_UNK6                         = 1 << 0x06,
        SPELL_ATTR_EX3_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX3_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX3_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX3_MAIN_HAND                    = 1 << 0x0A,
        SPELL_ATTR_EX3_BATTLEGROUND                 = 1 << 0x0B,
        SPELL_ATTR_EX3_CAST_ON_DEAD                 = 1 << 0x0C,
        SPELL_ATTR_EX3_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX3_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX3_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX3_UNK16                        = 1 << 0x10,
        SPELL_ATTR_EX3_UNK17                        = 1 << 0x11,
        SPELL_ATTR_EX3_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX3_UNK19                        = 1 << 0x13,
        SPELL_ATTR_EX3_DEATH_PERSISTENT             = 1 << 0x14,
        SPELL_ATTR_EX3_UNK21                        = 1 << 0x15,
        SPELL_ATTR_EX3_REQ_WAND                     = 1 << 0x16,
        SPELL_ATTR_EX3_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX3_REQ_OFFHAND                  = 1 << 0x18,
        SPELL_ATTR_EX3_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX3_UNK26                        = 1 << 0x1A,
        SPELL_ATTR_EX3_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX3_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX3_UNK29                        = 1 << 0x1D,
        SPELL_ATTR_EX3_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX3_UNK31                        = 1 << 0x1F
    };

    enum AttributesEx4
    {
        SPELL_ATTR_EX4_UNK0                         = 1 << 0x00,
        SPELL_ATTR_EX4_UNK1                         = 1 << 0x01,
        SPELL_ATTR_EX4_UNK2                         = 1 << 0x02,
        SPELL_ATTR_EX4_UNK3                         = 1 << 0x03,
        SPELL_ATTR_EX4_UNK4                         = 1 << 0x04,
        SPELL_ATTR_EX4_UNK5                         = 1 << 0x05,
        SPELL_ATTR_EX4_NOT_STEALABLE                = 1 << 0x06,
        SPELL_ATTR_EX4_UNK7                         = 1 << 0x07,
        SPELL_ATTR_EX4_UNK8                         = 1 << 0x08,
        SPELL_ATTR_EX4_UNK9                         = 1 << 0x09,
        SPELL_ATTR_EX4_SPELL_VS_EXTEND_COST         = 1 << 0x0A,
        SPELL_ATTR_EX4_UNK11                        = 1 << 0x0B,
        SPELL_ATTR_EX4_UNK12                        = 1 << 0x0C,
        SPELL_ATTR_EX4_UNK13                        = 1 << 0x0D,
        SPELL_ATTR_EX4_UNK14                        = 1 << 0x0E,
        SPELL_ATTR_EX4_UNK15                        = 1 << 0x0F,
        SPELL_ATTR_EX4_NOT_USABLE_IN_ARENA          = 1 << 0x10,
        SPELL_ATTR_EX4_USABLE_IN_ARENA              = 1 << 0x11,
        SPELL_ATTR_EX4_UNK18                        = 1 << 0x12,
        SPELL_ATTR_EX4_UNK19                        = 1 << 0x13,
        SPELL_ATTR_EX4_UNK20                        = 1 << 0x14,
        SPELL_ATTR_EX4_UNK21                        = 1 << 0x15,
        SPELL_ATTR_EX4_UNK22                        = 1 << 0x16,
        SPELL_ATTR_EX4_UNK23                        = 1 << 0x17,
        SPELL_ATTR_EX4_UNK24                        = 1 << 0x18,
        SPELL_ATTR_EX4_UNK25                        = 1 << 0x19,
        SPELL_ATTR_EX4_CAST_ONLY_IN_OUTLAND         = 1 << 0x1A,
        SPELL_ATTR_EX4_UNK27                        = 1 << 0x1B,
        SPELL_ATTR_EX4_UNK28                        = 1 << 0x1C,
        SPELL_ATTR_EX4_UNK29                        = 1 << 0x1D,
        SPELL_ATTR_EX4_UNK30                        = 1 << 0x1E,
        SPELL_ATTR_EX4_UNK31                        = 1 << 0x1F
    };

    enum AuraType
    {
        SPELL_AURA_NONE                             = 0,
        SPELL_AURA_BIND_SIGHT                       = 1,
        SPELL_AURA_MOD_POSSESS                      = 2,
        SPELL_AURA_PERIODIC_DAMAGE                  = 3,
        SPELL_AURA_DUMMY                            = 4,
        SPELL_AURA_MOD_CONFUSE                      = 5,
        SPELL_AURA_MOD_CHARM                        = 6,
        SPELL_AURA_MOD_FEAR                         = 7,
        SPELL_AURA_PERIODIC_HEAL                    = 8,
        SPELL_AURA_MOD_ATTACKSPEED                  = 9,
        SPELL_AURA_MOD_THREAT                       = 10,
        SPELL_AURA_MOD_TAUNT                        = 11,
        SPELL_AURA_MOD_STUN                         = 12,
        SPELL_AURA_MOD_DAMAGE_DONE                  = 13,
        SPELL_AURA_MOD_DAMAGE_TAKEN                 = 14,
        SPELL_AURA_DAMAGE_SHIELD                    = 15,
        SPELL_AURA_MOD_STEALTH                      = 16,
        SPELL_AURA_MOD_STEALTH_DETECT               = 17,
        SPELL_AURA_MOD_INVISIBILITY                 = 18,
        SPELL_AURA_MOD_INVISIBILITY_DETECTION       = 19,
        SPELL_AURA_OBS_MOD_HEALTH                   = 20,
        SPELL_AURA_OBS_MOD_MANA                     = 21,
        SPELL_AURA_MOD_RESISTANCE                   = 22,
        SPELL_AURA_PERIODIC_TRIGGER_SPELL           = 23,
        SPELL_AURA_PERIODIC_ENERGIZE                = 24,
        SPELL_AURA_MOD_PACIFY                       = 25,
        SPELL_AURA_MOD_ROOT                         = 26,
        SPELL_AURA_MOD_SILENCE                      = 27,
        SPELL_AURA_REFLECT_SPELLS                   = 28,
        SPELL_AURA_MOD_STAT                         = 29,
        SPELL_AURA_MOD_SKILL                        = 30,
        SPELL_AURA_MOD_INCREASE_SPEED               = 31,
        SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED       = 32,
        SPELL_AURA_MOD_DECREASE_SPEED               = 33,
        SPELL_AURA_MOD_INCREASE_HEALTH              = 34,
        SPELL_AURA_MOD_INCREASE_ENERGY              = 35,
        SPELL_AURA_MOD_SHAPESHIFT                   = 36,
        SPELL_AURA_EFFECT_IMMUNITY                  = 37,
        SPELL_AURA_STATE_IMMUNITY                   = 38,
        SPELL_AURA_SCHOOL_IMMUNITY                  = 39,
        SPELL_AURA_DAMAGE_IMMUNITY                  = 40,
        SPELL_AURA_DISPEL_IMMUNITY                  = 41,
        SPELL_AURA_PROC_TRIGGER_SPELL               = 42,
        SPELL_AURA_PROC_TRIGGER_DAMAGE              = 43,
        SPELL_AURA_TRACK_CREATURES                  = 44,
        SPELL_AURA_TRACK_RESOURCES                  = 45,
        SPELL_AURA_MOD_PARRY_SKILL                  = 46,
        SPELL_AURA_MOD_PARRY_PERCENT                = 47,
        SPELL_AURA_MOD_DODGE_SKILL                  = 48,
        SPELL_AURA_MOD_DODGE_PERCENT                = 49,
        SPELL_AURA_MOD_BLOCK_SKILL                  = 50,
        SPELL_AURA_MOD_BLOCK_PERCENT                = 51,
        SPELL_AURA_MOD_CRIT_PERCENT                 = 52,
        SPELL_AURA_PERIODIC_LEECH                   = 53,
        SPELL_AURA_MOD_HIT_CHANCE                   = 54,
        SPELL_AURA_MOD_SPELL_HIT_CHANCE             = 55,
        SPELL_AURA_TRANSFORM                        = 56,
        SPELL_AURA_MOD_SPELL_CRIT_CHANCE            = 57,
        SPELL_AURA_MOD_INCREASE_SWIM_SPEED          = 58,
        SPELL_AURA_MOD_DAMAGE_DONE_CREATURE         = 59,
        SPELL_AURA_MOD_PACIFY_SILENCE               = 60,
        SPELL_AURA_MOD_SCALE                        = 61,
        SPELL_AURA_PERIODIC_HEALTH_FUNNEL           = 62,
        SPELL_AURA_PERIODIC_MANA_FUNNEL             = 63,
        SPELL_AURA_PERIODIC_MANA_LEECH              = 64,
        SPELL_AURA_MOD_CASTING_SPEED                = 65,
        SPELL_AURA_FEIGN_DEATH                      = 66,
        SPELL_AURA_MOD_DISARM                       = 67,
        SPELL_AURA_MOD_STALKED                      = 68,
        SPELL_AURA_SCHOOL_ABSORB                    = 69,
        SPELL_AURA_EXTRA_ATTACKS                    = 70,
        SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL     = 71,
        SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT        = 72,
        SPELL_AURA_MOD_POWER_COST_SCHOOL            = 73,
        SPELL_AURA_REFLECT_SPELLS_SCHOOL            = 74,
        SPELL_AURA_MOD_LANGUAGE                     = 75,
        SPELL_AURA_FAR_SIGHT                        = 76,
        SPELL_AURA_MECHANIC_IMMUNITY                = 77,
        SPELL_AURA_MOUNTED                          = 78,
        SPELL_AURA_MOD_DAMAGE_PERCENT_DONE          = 79,
        SPELL_AURA_MOD_PERCENT_STAT                 = 80,
        SPELL_AURA_SPLIT_DAMAGE_PCT                 = 81,
        SPELL_AURA_WATER_BREATHING                  = 82,
        SPELL_AURA_MOD_BASE_RESISTANCE              = 83,
        SPELL_AURA_MOD_REGEN                        = 84,
        SPELL_AURA_MOD_POWER_REGEN                  = 85,
        SPELL_AURA_CHANNEL_DEATH_ITEM               = 86,
        SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN         = 87,
        SPELL_AURA_MOD_HEALTH_REGEN_PERCENT         = 88,
        SPELL_AURA_PERIODIC_DAMAGE_PERCENT          = 89,
        SPELL_AURA_MOD_RESIST_CHANCE                = 90,
        SPELL_AURA_MOD_DETECT_RANGE                 = 91,
        SPELL_AURA_PREVENTS_FLEEING                 = 92,
        SPELL_AURA_MOD_UNATTACKABLE                 = 93,
        SPELL_AURA_INTERRUPT_REGEN                  = 94,
        SPELL_AURA_GHOST                            = 95,
        SPELL_AURA_SPELL_MAGNET                     = 96,
        SPELL_AURA_MANA_SHIELD                      = 97,
        SPELL_AURA_MOD_SKILL_TALENT                 = 98,
        SPELL_AURA_MOD_ATTACK_POWER                 = 99,
        SPELL_AURA_AURAS_VISIBLE                    = 100,
        SPELL_AURA_MOD_RESISTANCE_PCT               = 101,
        SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS    = 102,
        SPELL_AURA_MOD_TOTAL_THREAT                 = 103,
        SPELL_AURA_WATER_WALK                       = 104,
        SPELL_AURA_FEATHER_FALL                     = 105,
        SPELL_AURA_HOVER                            = 106,
        SPELL_AURA_ADD_FLAT_MODIFIER                = 107,
        SPELL_AURA_ADD_PCT_MODIFIER                 = 108,
        SPELL_AURA_ADD_TARGET_TRIGGER               = 109,
        SPELL_AURA_MOD_POWER_REGEN_PERCENT          = 110,
        SPELL_AURA_ADD_CASTER_HIT_TRIGGER           = 111,
        SPELL_AURA_OVERRIDE_CLASS_SCRIPTS           = 112,
        SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN          = 113,
        SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT      = 114,
        SPELL_AURA_MOD_HEALING                      = 115,
        SPELL_AURA_MOD_REGEN_DURING_COMBAT          = 116,
        SPELL_AURA_MOD_MECHANIC_RESISTANCE          = 117,
        SPELL_AURA_MOD_HEALING_PCT                  = 118,
        SPELL_AURA_SHARE_PET_TRACKING               = 119,
        SPELL_AURA_UNTRACKABLE                      = 120,
        SPELL_AURA_EMPATHY                          = 121,
        SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT           = 122,
        SPELL_AURA_MOD_TARGET_RESISTANCE            = 123,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER          = 124,
        SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN           = 125,
        SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT       = 126,
        SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 127,
        SPELL_AURA_MOD_POSSESS_PET                  = 128,
        SPELL_AURA_MOD_SPEED_ALWAYS                 = 129,
        SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS         = 130,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS   = 131,
        SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT      = 132,
        SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT      = 133,
        SPELL_AURA_MOD_MANA_REGEN_INTERRUPT         = 134,
        SPELL_AURA_MOD_HEALING_DONE                 = 135,
        SPELL_AURA_MOD_HEALING_DONE_PERCENT         = 136,
        SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE        = 137,
        SPELL_AURA_MOD_HASTE                        = 138,
        SPELL_AURA_FORCE_REACTION                   = 139,
        SPELL_AURA_MOD_RANGED_HASTE                 = 140,
        SPELL_AURA_MOD_RANGED_AMMO_HASTE            = 141,
        SPELL_AURA_MOD_BASE_RESISTANCE_PCT          = 142,
        SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE         = 143,
        SPELL_AURA_SAFE_FALL                        = 144,
        SPELL_AURA_CHARISMA                         = 145,
        SPELL_AURA_PERSUADED                        = 146,
        SPELL_AURA_MECHANIC_IMMUNITY_MASK           = 147,
        SPELL_AURA_RETAIN_COMBO_POINTS              = 148,
        SPELL_AURA_RESIST_PUSHBACK                  = 149,
        SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT        = 150,
        SPELL_AURA_TRACK_STEALTHED                  = 151,
        SPELL_AURA_MOD_DETECTED_RANGE               = 152,
        SPELL_AURA_SPLIT_DAMAGE_FLAT                = 153,
        SPELL_AURA_MOD_STEALTH_LEVEL                = 154,
        SPELL_AURA_MOD_WATER_BREATHING              = 155,
        SPELL_AURA_MOD_REPUTATION_GAIN              = 156,
        SPELL_AURA_PET_DAMAGE_MULTI                 = 157,
        SPELL_AURA_MOD_SHIELD_BLOCKVALUE            = 158,
        SPELL_AURA_NO_PVP_CREDIT                    = 159,
        SPELL_AURA_MOD_AOE_AVOIDANCE                = 160,
        SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT       = 161,
        SPELL_AURA_POWER_BURN_MANA                  = 162,
        SPELL_AURA_MOD_CRIT_DAMAGE_BONUS_MELEE      = 163,
        SPELL_AURA_164                              = 164,
        SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 165,
        SPELL_AURA_MOD_ATTACK_POWER_PCT             = 166,
        SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT      = 167,
        SPELL_AURA_MOD_DAMAGE_DONE_VERSUS           = 168,
        SPELL_AURA_MOD_CRIT_PERCENT_VERSUS          = 169,
        SPELL_AURA_DETECT_AMORE                     = 170,
        SPELL_AURA_MOD_SPEED_NOT_STACK              = 171,
        SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK      = 172,
        SPELL_AURA_ALLOW_CHAMPION_SPELLS            = 173,
        SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT = 174,      // in 1.12.1 only dependent spirit case
        SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT = 175,
        SPELL_AURA_SPIRIT_OF_REDEMPTION             = 176,
        SPELL_AURA_AOE_CHARM                        = 177,
        SPELL_AURA_MOD_DEBUFF_RESISTANCE            = 178,
        SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE   = 179,
        SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS     = 180,
        SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS = 181,
        SPELL_AURA_MOD_RESISTANCE_OF_INTELLECT_PERCENT = 182,
        SPELL_AURA_MOD_CRITICAL_THREAT              = 183,
        SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE    = 184,
        SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE   = 185,
        SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE    = 186,
        SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE   = 187,
        SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE  = 188,
        SPELL_AURA_MOD_RATING                       = 189,
        SPELL_AURA_MOD_FACTION_REPUTATION_GAIN      = 190,
        SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED        = 191
    };

    enum ShapeshiftFormMask
    {
        FORM_NONE               = 0,
        FORM_CAT                = 1 << 0x00,
        FORM_TREE               = 1 << 0x01,
        FORM_TRAVEL             = 1 << 0x02,
        FORM_AQUA               = 1 << 0x03,
        FORM_BEAR               = 1 << 0x04,
        FORM_AMBIENT            = 1 << 0x05,
        FORM_GHOUL              = 1 << 0x06,
        FORM_DIREBEAR           = 1 << 0x07,
        FORM_STEVES_GHOUL       = 1 << 0x08,
        FORM_THARONJA_SKELETON  = 1 << 0x09,
        FORM_TEST_OF_STRENGTH   = 1 << 0x0A,
        FORM_BLB_PLAYER         = 1 << 0x0B,
        FORM_SHADOW_DANCE       = 1 << 0x0C,
        FORM_CREATUREBEAR       = 1 << 0x0D,
        FORM_CREATURECAT        = 1 << 0x0E,
        FORM_GHOSTWOLF          = 1 << 0x0F,
        FORM_BATTLESTANCE       = 1 << 0x10,
        FORM_DEFENSIVESTANCE    = 1 << 0x11,
        FORM_BERSERKERSTANCE    = 1 << 0x12,
        FORM_TEST               = 1 << 0x13,
        FORM_ZOMBIE             = 1 << 0x14,
        FORM_METAMORPHOSIS      = 1 << 0x15,
        FORM_UNK1               = 1 << 0x16,
        FORM_UNK2               = 1 << 0x17,
        FORM_UNDEAD             = 1 << 0x18,
        FORM_FRENZY             = 1 << 0x19,
        FORM_FLIGHT_EPIC        = 1 << 0x1A,
        FORM_SHADOW             = 1 << 0x1B,
        FORM_FLIGHT             = 1 << 0x1C,
        FORM_STEALTH            = 1 << 0x1D,
        FORM_MOONKIN            = 1 << 0x1E,
        FORM_SPIRITOFREDEMPTION = 1 << 0x1F
    };

    enum ItemClass
    {
        CONSUMABLE  = 0,
        CONTAINER   = 1,
        WEAPONS     = 2,
        GEM         = 3,
        ARMOR       = 4,
        REAGENT     = 5,
        PROJECTILE  = 6,
        TRADE_GOODS = 7,
        GENERIC     = 8,
        RECIPE      = 9,
        MONEY       = 10,
        QUIVER      = 11,
        QUEST       = 12,
        KEY         = 13,
        PERMANENT   = 14,
        MISC        = 15,
        MAX
    };

    enum ItemSubClassWeaponMask
    {
        AXE           = 1 << 0x00,
        AXE2          = 1 << 0x01,
        BOW           = 1 << 0x02,
        GUN           = 1 << 0x03,
        MACE          = 1 << 0x04,
        MACE2         = 1 << 0x05,
        POLEARM       = 1 << 0x06,
        SWORD         = 1 << 0x07,
        SWORD2        = 1 << 0x08,
        OBSOLETE      = 1 << 0x09,
        STAFF         = 1 << 0x0A,
        EXOTIC        = 1 << 0x0B,
        EXOTIC2       = 1 << 0x0C,
        FIST          = 1 << 0x0D,
        MISC_WEAPON   = 1 << 0x0E,
        DAGGER        = 1 << 0x0F,
        THROWNS       = 1 << 0x10,
        SPEAR         = 1 << 0x11,
        CROSSBOW      = 1 << 0x12,
        WAND          = 1 << 0x13,
        FISHING_POLE  = 1 << 0x14
    };

    enum ItemSubClassArmorMask
    {
        MISC_ARMOR= 1 << 0x0,
        CLOTH     = 1 << 0x1,
        LEATHER   = 1 << 0x2,
        MAIL      = 1 << 0x3,
        PLATE     = 1 << 0x4,
        BUCKLER   = 1 << 0x5,
        SHIELD    = 1 << 0x6,
        LIBRAM    = 1 << 0x7,
        IDOL      = 1 << 0x8,
        TOTEM     = 1 << 0x9,
        SIGIL     = 1 << 0xA
    };

    enum ItemSubClassMiscMask
    {
        JUNK          = 1 << 0x0,
        MISC_REAGENT  = 1 << 0x1,
        PET           = 1 << 0x2,
        HOLIDAY       = 1 << 0x3,
        OTHER         = 1 << 0x4,
        MOUNT         = 1 << 0x5,
    };

    enum InventoryTypeMask
    {
        NON_EQUIP       = 1 << 0x00,
        HEAD            = 1 << 0x01,
        NECK            = 1 << 0x02,
        SHOULDERS       = 1 << 0x03,
        BODY            = 1 << 0x04,
        CHEST           = 1 << 0x05,
        WAIST           = 1 << 0x06,
        LEGS            = 1 << 0x07,
        FEET            = 1 << 0x08,
        WRISTS          = 1 << 0x09,
        HANDS           = 1 << 0x0A,
        FINGER          = 1 << 0x0B,
        TRINKET         = 1 << 0x0C,
        WEAPON          = 1 << 0x0D,
        SHIELD_INV      = 1 << 0x0E,
        RANGED          = 1 << 0x0F,
        CLOAK           = 1 << 0x10,
        WEAPON_2H       = 1 << 0x11,
        BAG             = 1 << 0x12,
        TABARD          = 1 << 0x13,
        ROBE            = 1 << 0x14,
        WEAPONMAINHAND  = 1 << 0x15,
        WEAPONOFFHAND   = 1 << 0x16,
        HOLDABLE        = 1 << 0x17,
        AMMO            = 1 << 0x18,
        THROWN          = 1 << 0x19,
        RANGEDRIGHT     = 1 << 0x1A,
        QUIVER_INV      = 1 << 0x1B,
        RELIC           = 1 << 0x1C,
    };

    enum CombatRating
    {
        CR_WEAPON_SKILL             =      0x00,
        CR_DEFENSE_SKILL            = 1 << 0x00,
        CR_DODGE                    = 1 << 0x01,
        CR_PARRY                    = 1 << 0x02,
        CR_BLOCK                    = 1 << 0x03,
        CR_HIT_MELEE                = 1 << 0x04,
        CR_HIT_RANGED               = 1 << 0x05,
        CR_HIT_SPELL                = 1 << 0x06,
        CR_CRIT_MELEE               = 1 << 0x07,
        CR_CRIT_RANGED              = 1 << 0x08,
        CR_CRIT_SPELL               = 1 << 0x09,
        CR_HIT_TAKEN_MELEE          = 1 << 0x0A,
        CR_HIT_TAKEN_RANGED         = 1 << 0x0B,
        CR_HIT_TAKEN_SPELL          = 1 << 0x0C,
        CR_CRIT_TAKEN_MELEE         = 1 << 0x0D,
        CR_CRIT_TAKEN_RANGED        = 1 << 0x0E,
        CR_CRIT_TAKEN_SPELL         = 1 << 0x0F,
        CR_HASTE_MELEE              = 1 << 0x10,
        CR_HASTE_RANGED             = 1 << 0x11,
        CR_HASTE_SPELL              = 1 << 0x12,
        CR_WEAPON_SKILL_MAINHAND    = 1 << 0x13,
        CR_WEAPON_SKILL_OFFHAND     = 1 << 0x14,
        CR_WEAPON_SKILL_RANGED      = 1 << 0x15,
        CR_EXPERTISE                = 1 << 0x16,
        CR_ARMOR_PENETRATION        = 1 << 0x17,
    };

    enum DispelType
    {
        DISPEL_NONE         = 0,
        DISPEL_MAGIC        = 1,
        DISPEL_CURSE        = 2,
        DISPEL_DISEASE      = 3,
        DISPEL_POISON       = 4,
        DISPEL_STEALTH      = 5,
        DISPEL_INVISIBILITY = 6,
        DISPEL_ALL          = 7,
        DISPEL_SPE_NPC_ONLY = 8,
        DISPEL_ENRAGE       = 9,
        DISPEL_ZG_TICKET    = 10
    };

    enum AuraState
    {
        AURA_STATE_NONE                     = 0,
        AURA_STATE_DEFENSE                  = 1,
        AURA_STATE_HEALTHLESS_20_PERCENT    = 2,
        AURA_STATE_BERSERKING               = 3,
        AURA_STATE_FROZEN                   = 4,
        AURA_STATE_JUDGEMENT                = 5,
        AURA_STATE_UNKNOWN6                 = 6,
        AURA_STATE_HUNTER_PARRY             = 7,
        AURA_STATE_ROGUE_ATTACK_FROM_STEALTH    = 7
    };

    enum Targets
    {
        NO_TARGET                               = 0,
        TARGET_SELF                             = 1,
        TARGET_RANDOM_ENEMY_CHAIN_IN_AREA       = 2,
        TARGET_RANDOM_FRIEND_CHAIN_IN_AREA      = 3,
        TARGET_4                                = 4,
        TARGET_PET                              = 5,
        TARGET_CHAIN_DAMAGE                     = 6,
        TARGET_AREAEFFECT_INSTANT               = 7,
        TARGET_AREAEFFECT_CUSTOM                = 8,
        TARGET_INNKEEPER_COORDINATES            = 9,
        TARGET_10                               = 10,
        TARGET_11                               = 11,
        TARGET_12                               = 12,
        TARGET_13                               = 13,
        TARGET_14                               = 14,
        TARGET_ALL_ENEMY_IN_AREA                = 15,
        TARGET_ALL_ENEMY_IN_AREA_INSTANT        = 16,
        TARGET_TABLE_X_Y_Z_COORDINATES          = 17,
        TARGET_EFFECT_SELECT                    = 18,
        TARGET_19                               = 19,
        TARGET_ALL_PARTY_AROUND_CASTER          = 20,
        TARGET_SINGLE_FRIEND                    = 21,
        TARGET_CASTER_COORDINATES               = 22,
        TARGET_GAMEOBJECT                       = 23,
        TARGET_IN_FRONT_OF_CASTER               = 24,
        TARGET_DUELVSPLAYER                     = 25,
        TARGET_GAMEOBJECT_ITEM                  = 26,
        TARGET_MASTER                           = 27,
        TARGET_ALL_ENEMY_IN_AREA_CHANNELED      = 28,
        TARGET_29                               = 29,
        TARGET_ALL_FRIENDLY_UNITS_AROUND_CASTER = 30,
        TARGET_ALL_FRIENDLY_UNITS_IN_AREA       = 31,
        TARGET_MINION                           = 32,
        TARGET_ALL_PARTY                        = 33,
        TARGET_ALL_PARTY_AROUND_CASTER_2        = 34,
        TARGET_SINGLE_PARTY                     = 35,
        TARGET_ALL_HOSTILE_UNITS_AROUND_CASTER  = 36,
        TARGET_AREAEFFECT_PARTY                 = 37,
        TARGET_SCRIPT                           = 38,
        TARGET_SELF_FISHING                     = 39,
        TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT     = 40,
        TARGET_TOTEM_EARTH                      = 41,
        TARGET_TOTEM_WATER                      = 42,
        TARGET_TOTEM_AIR                        = 43,
        TARGET_TOTEM_FIRE                       = 44,
        TARGET_CHAIN_HEAL                       = 45,
        TARGET_SCRIPT_COORDINATES               = 46,
        TARGET_DYNAMIC_OBJECT_FRONT             = 47,
        TARGET_DYNAMIC_OBJECT_BEHIND            = 48,
        TARGET_DYNAMIC_OBJECT_LEFT_SIDE         = 49,
        TARGET_DYNAMIC_OBJECT_RIGHT_SIDE        = 50,
        TARGET_51                               = 51,
        TARGET_AREAEFFECT_GO_AROUND_DEST        = 52,
        TARGET_CURRENT_ENEMY_COORDINATES        = 53,
        TARGET_LARGE_FRONTAL_CONE               = 54,
        TARGET_55                               = 55,
        TARGET_ALL_RAID_AROUND_CASTER           = 56,
        TARGET_SINGLE_FRIEND_2                  = 57,
        TARGET_58                               = 58,
        TARGET_59                               = 59,
        TARGET_NARROW_FRONTAL_CONE              = 60,
        TARGET_AREAEFFECT_PARTY_AND_CLASS       = 61,
        TARGET_62                               = 62,
        TARGET_DUELVSPLAYER_COORDINATES         = 63
    };

    enum UnitMods
    {
        UNIT_MOD_STAT_STRENGTH          = 0,
        UNIT_MOD_STAT_AGILITY           = 1,
        UNIT_MOD_STAT_STAMINA           = 2,
        UNIT_MOD_STAT_INTELLECT         = 3,
        UNIT_MOD_STAT_SPIRIT            = 4,
        UNIT_MOD_HEALTH                 = 5,
        UNIT_MOD_MANA                   = 6,
        UNIT_MOD_RAGE                   = 7,
        UNIT_MOD_FOCUS                  = 8,
        UNIT_MOD_ENERGY                 = 9,
        UNIT_MOD_HAPPINESS              = 10,
        UNIT_MOD_RUNE                   = 11,
        UNIT_MOD_RUNIC_POWER            = 12,
        UNIT_MOD_ARMOR                  = 13,
        UNIT_MOD_RESISTANCE_HOLY        = 14,
        UNIT_MOD_RESISTANCE_FIRE        = 15,
        UNIT_MOD_RESISTANCE_NATURE      = 16,
        UNIT_MOD_RESISTANCE_FROST       = 17,
        UNIT_MOD_RESISTANCE_SHADOW      = 18,
        UNIT_MOD_RESISTANCE_ARCANE      = 19,
        UNIT_MOD_ATTACK_POWER           = 20,
        UNIT_MOD_ATTACK_POWER_RANGED    = 21,
        UNIT_MOD_DAMAGE_MAINHAND        = 22,
        UNIT_MOD_DAMAGE_OFFHAND         = 23,
        UNIT_MOD_DAMAGE_RANGED          = 24,
        UNIT_MOD_END                    = 25,
        // synonyms
        UNIT_MOD_STAT_START             = UNIT_MOD_STAT_STRENGTH,
        UNIT_MOD_STAT_END               = UNIT_MOD_STAT_SPIRIT       + 1,
        UNIT_MOD_RESISTANCE_START       = UNIT_MOD_ARMOR,
        UNIT_MOD_RESISTANCE_END         = UNIT_MOD_RESISTANCE_ARCANE + 1,
        UNIT_MOD_POWER_START            = UNIT_MOD_MANA,
        UNIT_MOD_POWER_END              = UNIT_MOD_RUNIC_POWER       + 1
    };

    enum SpellModOp
    {
        SPELLMOD_DAMAGE                 = 0,
        SPELLMOD_DURATION               = 1,
        SPELLMOD_THREAT                 = 2,
        SPELLMOD_EFFECT1                = 3,
        SPELLMOD_CHARGES                = 4,
        SPELLMOD_RANGE                  = 5,
        SPELLMOD_RADIUS                 = 6,
        SPELLMOD_CRITICAL_CHANCE        = 7,
        SPELLMOD_ALL_EFFECTS            = 8,
        SPELLMOD_NOT_LOSE_CASTING_TIME  = 9,
        SPELLMOD_CASTING_TIME           = 10,
        SPELLMOD_COOLDOWN               = 11,
        SPELLMOD_EFFECT2                = 12,
        SPELLMOD_13                     = 13,
        SPELLMOD_COST                   = 14,
        SPELLMOD_CRIT_DAMAGE_BONUS      = 15,
        SPELLMOD_RESIST_MISS_CHANCE     = 16,
        SPELLMOD_JUMP_TARGETS           = 17,
        SPELLMOD_CHANCE_OF_SUCCESS      = 18,
        SPELLMOD_ACTIVATION_TIME        = 19,
        SPELLMOD_EFFECT_PAST_FIRST      = 20,
        SPELLMOD_CASTING_TIME_OLD       = 21,
        SPELLMOD_DOT                    = 22,
        SPELLMOD_EFFECT3                = 23,
        SPELLMOD_SPELL_BONUS_DAMAGE     = 24,
        SPELLMOD_25                     = 25,
        SPELLMOD_FREQUENCY_OF_SUCCESS   = 26,
        SPELLMOD_MULTIPLE_VALUE         = 27,
        SPELLMOD_RESIST_DISPEL_CHANCE   = 28
    };

    enum SpellFamilyNames
    {
        SPELLFAMILY_GENERIC     = 0,
        SPELLFAMILY_UNK1        = 1,
        // unused               = 2,
        SPELLFAMILY_MAGE        = 3,
        SPELLFAMILY_WARRIOR     = 4,
        SPELLFAMILY_WARLOCK     = 5,
        SPELLFAMILY_PRIEST      = 6,
        SPELLFAMILY_DRUID       = 7,
        SPELLFAMILY_ROGUE       = 8,
        SPELLFAMILY_HUNTER      = 9,
        SPELLFAMILY_PALADIN     = 10,
        SPELLFAMILY_SHAMAN      = 11,
        SPELLFAMILY_UNK2        = 12,
        SPELLFAMILY_POTION      = 13,
        // unused               = 14,
        // unused               = 15,
        // unused               = 16,
        SPELLFAMILY_PET         = 17
    };

    enum Powers
    {
        POWER_MANA          = 0,
        POWER_RAGE          = 1,
        POWER_FOCUS         = 2,
        POWER_ENERGY        = 3,
        POWER_HAPPINESS     = 4,
        POWER_RUNE          = 5,
        POWER_RUNIC_POWER   = 6,
        POWER_HEALTH        = -2,
    };

    Q_ENUMS(LocalesDBC)
    Q_ENUMS(Mechanic)
    Q_ENUMS(PreventionType)
    Q_ENUMS(DamageClass)
    Q_ENUMS(School)
    Q_ENUMS(Effects)
    Q_ENUMS(TargetFlags)
    Q_ENUMS(CreatureTypeMask)
    Q_ENUMS(Attributes)
    Q_ENUMS(AttributesEx)
    Q_ENUMS(AttributesEx2)
    Q_ENUMS(AttributesEx3)
    Q_ENUMS(AttributesEx4)
    Q_ENUMS(AuraType)
    Q_ENUMS(ShapeshiftFormMask)
    Q_ENUMS(ItemClass)
    Q_ENUMS(ItemSubClassWeaponMask)
    Q_ENUMS(ItemSubClassArmorMask)
    Q_ENUMS(ItemSubClassMiscMask)
    Q_ENUMS(InventoryTypeMask)
    Q_ENUMS(CombatRating)
    Q_ENUMS(DispelType)
    Q_ENUMS(AuraState)
    Q_ENUMS(Targets)
    Q_ENUMS(UnitMods)
    Q_ENUMS(SpellModOp)
    Q_ENUMS(SpellFamilyNames)
    Q_ENUMS(Powers)
};


#endif
