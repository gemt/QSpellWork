#include "structure.h"
#include "spellinfo.h"

// SkillLine.dbc
DBCFile& SkillLine::getDbc()
{
    static DBCFile dbc("SkillLine.dbc");
    return dbc;
}

const DBCFileHeader* SkillLine::getHeader()
{ 
    return getDbc().getHeader();
}

const SkillLine::entry* SkillLine::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SkillLine::entry::name() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(nameOffset[m_locale]));
}

const QString SkillLine::entry::description() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(descriptionOffset[m_locale]));
}

// SkillLineAbility.dbc
DBCFile& SkillLineAbility::getDbc()
{
    static DBCFile dbc("SkillLineAbility.dbc");
    return dbc;
}

const DBCFileHeader* SkillLineAbility::getHeader()
{ 
    return getDbc().getHeader();
}

const SkillLineAbility::entry* SkillLineAbility::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// Spell.dbc
DBCFile& Spell::getDbc()
{
    static DBCFile dbc("Spell.dbc");
    return dbc;
}

const DBCFileHeader* Spell::getHeader()
{
    return getDbc().getHeader();
}

const Spell::entry* Spell::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString Spell::entry::name() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(nameOffset[m_locale]));
}

const QString Spell::entry::description() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(descriptionOffset[m_locale]));
}

const QString Spell::entry::rank() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(rankOffset[m_locale]));
}

const QString Spell::entry::toolTip() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(toolTipOffset[m_locale]));
}

const QString Spell::entry::nameWithRank() const
{
    return (!rank().isEmpty() ? name() + " (" + rank() + ")" : name());
}

qint32 Spell::entry::getTriggerDuration(quint8 index) const
{
    const Spell::entry* triggerSpell = Spell::getRecord(effectTriggerSpell[index], true);
    if (triggerSpell)
        return triggerSpell->getDuration();

    return 0;
}

// SpellCastTimes.dbc
DBCFile& SpellCastTimes::getDbc()
{
    static DBCFile dbc("SpellCastTimes.dbc");
    return dbc;
}

const DBCFileHeader* SpellCastTimes::getHeader()
{ 
    return getDbc().getHeader();
}

const SpellCastTimes::entry* SpellCastTimes::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRadius.dbc
DBCFile& SpellRadius::getDbc()
{
    static DBCFile dbc("SpellRadius.dbc");
    return dbc;
}

const DBCFileHeader* SpellRadius::getHeader()
{ 
    return getDbc().getHeader();
}

const SpellRadius::entry* SpellRadius::getRecord(quint32 id, bool realId)
{
   return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellRange.dbc
DBCFile& SpellRange::getDbc()
{
    static DBCFile dbc("SpellRange.dbc");
    return dbc;
}

const DBCFileHeader* SpellRange::getHeader()
{ 
    return getDbc().getHeader();
}

const SpellRange::entry* SpellRange::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellRange::entry::name() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(nameOffset[m_locale]));
}

const QString SpellRange::entry::shortName() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(shortNameOffset[m_locale]));
}

// SpellDuration.dbc
DBCFile& SpellDuration::getDbc()
{
    static DBCFile dbc("SpellDuration.dbc");
    return dbc;
}

const DBCFileHeader* SpellDuration::getHeader()
{ 
    return getDbc().getHeader();
}

const SpellDuration::entry* SpellDuration::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellIcon.dbc
DBCFile& SpellIcon::getDbc()
{
    static DBCFile dbc("SpellIcon.dbc");
    return dbc;
}

const DBCFileHeader* SpellIcon::getHeader()
{ 
    return getDbc().getHeader();
}

const SpellIcon::entry* SpellIcon::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellIcon::entry::iconPath() const
{
    return QString::fromUtf8(getDbc().getStringBlock() + quint32(iconPathOffset));
}
