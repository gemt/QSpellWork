#include <QBuffer>
#include <QThread>

#include "SWObject.h"
#include "SWModels.h"
#include "Defines.h"
#include "blp/BLP.h"

Q_DECLARE_METATYPE(Spell::meta*)

SWObject::SWObject(MainForm* form)
    : QObject(form), m_form(form), m_regExp(false), m_type(0), m_enums(form->getEnums())
{
}

QList<QEvent*> SWObject::search()
{
    SpellListModel *model = new SpellListModel();
    QList<QEvent*> eventList;

    if (getType() == 1)
    {
        for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        {
            bool family = false;
            bool aura = false;
            bool effect = false;
            bool targetA = false;
            bool targetB = false;

            if (const Spell::entry* m_spellInfo = Spell::getRecord(i))
            {
                if (m_form->comboBox->currentIndex() > 0)
                {
                    quint16 familyId = m_form->comboBox->itemData(m_form->comboBox->currentIndex()).toInt();
                    if (m_spellInfo->spellFamilyName == familyId)
                        family = true;
                }
                else
                    family = true;

                if (m_form->comboBox_2->currentIndex() > 0)
                {
                    quint16 auraId = m_form->comboBox_2->itemData(m_form->comboBox_2->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectApplyAuraName[i] == auraId)
                        {
                            aura = true;
                            break;
                        }
                    }
                }
                else
                    aura = true;

                if (m_form->comboBox_3->currentIndex() > 0)
                {
                    quint16 effectId = m_form->comboBox_3->itemData(m_form->comboBox_3->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effect[i] == effectId)
                        {
                            effect = true;
                            break;
                        }
                    }
                }
                else
                    effect = true;

                if (m_form->comboBox_4->currentIndex() > 0)
                {
                    quint16 targetId = m_form->comboBox_4->itemData(m_form->comboBox_4->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectImplicitTargetA[i] == targetId)
                        {
                            targetA = true;
                            break;
                        }
                    }
                }
                else
                    targetA = true;

                if (m_form->comboBox_5->currentIndex() > 0)
                {
                    quint16 targetId = m_form->comboBox_5->itemData(m_form->comboBox_5->currentIndex()).toInt();
                    for (quint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
                    {
                        if (m_spellInfo->effectImplicitTargetB[i] == targetId)
                        {
                            targetB = true;
                            break;
                        }
                    }
                }
                else
                    targetB = true;

                if (family && aura && effect && targetA && targetB)
                {
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }
        }
        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else if (getType() == 3)
    {
        QJSEngine engine;

        EnumHash enums = m_form->getEnums()->getEnums();

        for (EnumHash::const_iterator itr = enums.begin(); itr != enums.end(); ++itr)
            for (Enumerator::const_iterator itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
                engine.globalObject().setProperty(itr2.value(), qreal(itr2.key()));

        QJSValue script = engine.evaluate("(function() { return (" + m_form->getFilterText() + "); })");

        for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        {
            const Spell::entry* m_spellInfo = Spell::getRecord(i);

            if (!m_spellInfo)
                continue;

            Spell::meta metaSpell(m_spellInfo);

            engine.globalObject().setProperty("spell", engine.newQObject(&metaSpell));

            if (script.call(QJSValueList()).toBool())
            {
                QString sRank(m_spellInfo->rank());
                QString sFullName(m_spellInfo->name());

                if (!sRank.isEmpty())
                    sFullName.append(QString(" (%0)").arg(sRank));

                QStringList spellRecord;
                spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                model->appendRecord(spellRecord);
            }
        }

        Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
        ev->addValue(QVariant::fromValue(model));
        eventList << ev;
    }
    else
    {
        if (!m_form->findLine_e1->text().isEmpty())
        {
            if (!m_form->findLine_e1->text().toInt())
            {
                for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
                {
                    const Spell::entry* m_spellInfo = Spell::getRecord(i);
                    if (m_spellInfo && m_spellInfo->name().contains(m_form->findLine_e1->text(), Qt::CaseInsensitive))
                    {
                        QString sRank(m_spellInfo->rank());
                        QString sFullName(m_spellInfo->name());

                        if (!sRank.isEmpty())
                            sFullName.append(QString(" (%0)").arg(sRank));

                        QStringList spellRecord;
                        spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                        model->appendRecord(spellRecord);
                    }
                }

                Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                ev->addValue(QVariant::fromValue(model));
                eventList << ev;
            }
            else
            {
                if (const Spell::entry* m_spellInfo = Spell::getRecord(m_form->findLine_e1->text().toInt(), true))
                {
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                    model->appendRecord(spellRecord);

                    Event* ev1 = new Event(Event::Type(Event::EVENT_SEND_MODEL));
                    ev1->addValue(QVariant::fromValue(model));
                    eventList << ev1;

                    Event* ev2 = new Event(Event::Type(Event::EVENT_SEND_SPELL));
                    ev2->addValue(m_spellInfo->id);
                    eventList << ev2;
                }
            }
        }
        else if (!m_form->findLine_e3->text().isEmpty())
        {
            for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
            {
                const Spell::entry* m_spellInfo = Spell::getRecord(i);
                if (m_spellInfo && m_spellInfo->description().contains(m_form->findLine_e3->text(), Qt::CaseInsensitive))
                {
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
        else
        {
            for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
            {
                if (const Spell::entry* m_spellInfo = Spell::getRecord(i))
                {
                    QString sRank(m_spellInfo->rank());
                    QString sFullName(m_spellInfo->name());

                    if (!sRank.isEmpty())
                        sFullName.append(QString(" (%0)").arg(sRank));

                    QStringList spellRecord;
                    spellRecord << QString("%0").arg(m_spellInfo->id) << sFullName;

                    model->appendRecord(spellRecord);
                }
            }

            Event* ev = new Event(Event::Type(Event::EVENT_SEND_MODEL));
            ev->addValue(QVariant::fromValue(model));
            eventList << ev;
        }
    }

    return eventList;
}

void SWObject::setMetaEnum(const char* enumName)
{
    m_metaEnum = Enums::staticMetaObject.enumerator(Enums::staticMetaObject.indexOfEnumerator(enumName));
}

float getRadius(const Spell::entry* spellInfo, quint8 effIndex)
{
    if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(spellInfo->effectRadiusIndex[effIndex], true))
        return spellRadius->radius;

    return 0.0f;
}

quint32 getDuration(const Spell::entry* spellInfo)
{
    if (const SpellDuration::entry* durationInfo = SpellDuration::getRecord(spellInfo->durationIndex, true))
        return quint32(durationInfo->duration / 1000);

    return 1;
}

quint32 getRealDuration(const Spell::entry* spellInfo, quint8 effIndex)
{
    return quint32(getDuration(spellInfo) / (spellInfo->effectAmplitude[effIndex] ? quint32(spellInfo->effectAmplitude[effIndex] / 1000) : 5));
}

void RegExpU(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->stackAmount));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->stackAmount));
    }
}

void RegExpH(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->procChance));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->procChance));
    }
}

void RegExpV(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->maxTargetLevel));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->maxTargetLevel));
    }
}

void RegExpQ(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32(tSpell->effectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValue[rx.cap(6).toInt()-1] / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32(spellInfo->effectMiscValue[rx.cap(6).toInt()-1] * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->effectMiscValue[rx.cap(6).toInt()-1])));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->effectMiscValue[rx.cap(6).toInt()-1])));
    }
}

void RegExpI(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            if (tSpell->maxAffectedTargets != 0)
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(tSpell->maxAffectedTargets));
            }
            else
            {
                str.replace(rx.cap(0), QString("nearby"));
            }
        }
    }
    else
    {
        if (spellInfo->maxAffectedTargets != 0)
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(spellInfo->maxAffectedTargets));
        }
        else
        {
            str.replace(rx.cap(0), QString("nearby"));
        }
    }
}

void RegExpB(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(qint32(tSpell->effectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(qint32(spellInfo->effectPointsPerComboPoint[rx.cap(6).toInt()-1]))));
    }
}

void RegExpA(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry * tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getRadius(tSpell, rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getRadius(tSpell, rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getRadius(spellInfo, rx.cap(6).toInt()-1) / rx.cap(2).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getRadius(spellInfo, rx.cap(6).toInt()-1) * rx.cap(2).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRadius(tSpell, rx.cap(6).toInt()-1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRadius(spellInfo, rx.cap(6).toInt()-1)));
    }
}

void RegExpD(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getDuration(tSpell) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(getDuration(tSpell) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getDuration(spellInfo) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(getDuration(spellInfo) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0 seconds")
                .arg(getDuration(tSpell)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0 seconds")
            .arg(getDuration(spellInfo)));
    }
}

void RegExpO(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
                }
                else if(rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32((getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32((getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(getRealDuration(tSpell, rx.cap(6).toInt()-1) * (tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(getRealDuration(spellInfo, rx.cap(6).toInt()-1) * (spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpS(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(abs(qint32((tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1) / rx.cap(3).toInt()))));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(abs(qint32((spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1) * rx.cap(3).toInt()))));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(abs(tSpell->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(abs(spellInfo->effectBasePoints[rx.cap(6).toInt()-1] + 1)));
    }
}

void RegExpT(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(3).isEmpty())
    {
        if (!rx.cap(4).isEmpty())
        {
            if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
            {
                if (rx.cap(2) == QString("/"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
                }
                else if (rx.cap(2) == QString("*"))
                {
                    str.replace(rx.cap(0), QString("%0")
                        .arg(quint32(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
                }
            }
        }
        else
        {
            if (rx.cap(2) == QString("/"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000) / rx.cap(3).toInt())));
            }
            else if (rx.cap(2) == QString("*"))
            {
                str.replace(rx.cap(0), QString("%0")
                    .arg(quint32(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000) * rx.cap(3).toInt())));
            }
        }
    }
    else if (!rx.cap(4).isEmpty())
    {
        
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            if (tSpell->effectAmplitude[rx.cap(6).toInt()-1])
                str.replace(rx.cap(0), QString("%0").arg(quint32(tSpell->effectAmplitude[rx.cap(6).toInt()-1] / 1000)));
            else
                str.replace(rx.cap(0), QString("%0").arg(quint32(tSpell->getAmplitude() / 1000)));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(quint32(spellInfo->effectAmplitude[rx.cap(6).toInt()-1] / 1000)));
    }
}

void RegExpN(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->procCharges));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->procCharges));
    }
}

void RegExpX(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->effectChainTarget[rx.cap(6).toInt()-1]));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->effectChainTarget[rx.cap(6).toInt()-1]));
    }
}

void RegExpE(const Spell::entry* spellInfo, QRegExp rx, QString &str)
{
    if (!rx.cap(4).isEmpty())
    {
        if (const Spell::entry* tSpell = Spell::getRecord(rx.cap(4).toInt(), true))
        {
            str.replace(rx.cap(0), QString("%0")
                .arg(tSpell->effectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
        }
    }
    else
    {
        str.replace(rx.cap(0), QString("%0")
            .arg(spellInfo->effectMultipleValue[rx.cap(6).toInt()-1], 0, 'f', 2));
    }
}

QString SWObject::getDescription(QString str, const Spell::entry* spellInfo)
{
    if (!m_form->isRegExp())
        return str;

    QRegExp rx("\\$+(([/,*])?([0-9]*);)?([d+\\;)(\\d*)?([1-9]*)([A-z])([1-3]*)(([A-z, ]*)\\:([A-z, ]*)\\;)?");
    while (str.contains(rx))
    {
        if (rx.indexIn(str) != -1)
        {
            QChar symbol = rx.cap(5)[0].toLower();
            switch (symbol.toLatin1())
            {
                case 'u': RegExpU(spellInfo, rx, str); break;
                case 'h': RegExpH(spellInfo, rx, str); break;
                case 'v': RegExpV(spellInfo, rx, str); break;
                case 'q': RegExpQ(spellInfo, rx, str); break;
                case 'i': RegExpI(spellInfo, rx, str); break;
                case 'b': RegExpB(spellInfo, rx, str); break;
                case 'm':
                case 's':
                    RegExpS(spellInfo, rx, str);
                    break;
                case 'a': RegExpA(spellInfo, rx, str); break;
                case 'd': RegExpD(spellInfo, rx, str); break;
                case 'o': RegExpO(spellInfo, rx, str); break;
                case 't': RegExpT(spellInfo, rx, str); break;
                case 'n': RegExpN(spellInfo, rx, str); break;
                case 'x': RegExpX(spellInfo, rx, str); break;
                case 'e': RegExpE(spellInfo, rx, str); break;
                case 'l': str.replace(rx.cap(0), rx.cap(9)); break;
                case 'g': str.replace(rx.cap(0), rx.cap(8)); break;
                case 'z': str.replace(rx.cap(0), QString("[Home]")); break;
                default: return str;
            }
        }
    }
    return str;
}

quint32 SWObject::getParentSpellId(quint32 triggerId)
{
    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
        if (const Spell::entry* spellInfo = Spell::getRecord(i))
            for (quint8 eff = 0; eff < MAX_EFFECT_INDEX; ++eff)
                if (spellInfo->effectTriggerSpell[eff] == triggerId)
                    return spellInfo->id;
    return 0;
}

QString SWObject::getSpellIconName(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? iconInfo->iconPath().section('\\', -1) : QString(""));
}

QImage SWObject::getSpellIcon(quint32 iconId)
{
    const SpellIcon::entry* iconInfo = SpellIcon::getRecord(iconId, true);

    return (iconInfo ? BLP::getImage(iconInfo->iconPath() + QString(".blp")) : QImage());
}

void SWObject::showInfo(const Spell::entry* spellInfo, quint8 num)
{
    if (!spellInfo)
        return;

    QWebEngineView* browser = m_form->getBrowser(num);
    html.clear();

    QString sName(spellInfo->name());
    QString sDescription(spellInfo->description());
    QString sRank(spellInfo->rank());
    QString sToolTip(spellInfo->toolTip());
    QString sSpellFamilyFlags(QString("%0").arg(spellInfo->spellFamilyFlags, 16, 16, QChar('0')));
    QString sAttributes(QString("%0").arg(spellInfo->attributes, 8, 16, QChar('0')));
    QString sAttributesEx1(QString("%0").arg(spellInfo->attributesEx1, 8, 16, QChar('0')));
    QString sAttributesEx2(QString("%0").arg(spellInfo->attributesEx2, 8, 16, QChar('0')));
    QString sAttributesEx3(QString("%0").arg(spellInfo->attributesEx3, 8, 16, QChar('0')));
    QString sAttributesEx4(QString("%0").arg(spellInfo->attributesEx4, 8, 16, QChar('0')));
    QString sTargetMask(QString("%0").arg(spellInfo->targets, 8, 16, QChar('0')));
    QString sCreatureTypeMask(QString("%0").arg(spellInfo->targetCreatureType, 8, 16, QChar('0')));
    QString sFormMask(QString("%0").arg(spellInfo->stances, 8, 16, QChar('0')));
    QString sIF(QString("%0").arg(spellInfo->interruptFlags, 8, 16, QChar('0')));
    QString sAIF(QString("%0").arg(spellInfo->auraInterruptFlags, 8, 16, QChar('0')));
    QString sCIF(QString("%0").arg(spellInfo->channelInterruptFlags, 8, 16, QChar('0')));

    html.append("<html>"
                "<head>"
                "<link rel='stylesheet' type='text/css' href='qrc:///qsw/resources/styles.css'>"
                "</head>");

    html.append(QString("<body>"));

    QByteArray byteArray[3];
    QBuffer buffer[3];
    buffer[0].setBuffer(&byteArray[0]);
    buffer[0].open(QIODevice::WriteOnly);
    getSpellIcon(spellInfo->spellIconId).save(&buffer[0], "PNG");

    buffer[1].setBuffer(&byteArray[1]);
    buffer[1].open(QIODevice::WriteOnly);
    QImage(":/qsw/resources/border.png").save(&buffer[1], "PNG");

    buffer[2].setBuffer(&byteArray[2]);
    buffer[2].open(QIODevice::WriteOnly);
    QImage(":/qsw/resources/borderHover.png").save(&buffer[2], "PNG");

    html.append(QString("<div class='b-tooltip_icon'>"
                        "<style>"
                        "div.icon { width: 68px; height: 68px; background: url(\"data:image/png;base64," + byteArray[0].toBase64() + "\") no-repeat center; }"
                        "div.icon div { background: url(\"data:image/png;base64," + byteArray[1].toBase64() + "\") no-repeat center;}"
                        "div.icon div div:hover { background: url(\"data:image/png;base64," + byteArray[2].toBase64() + "\") no-repeat center; }"
                        "div.icon div div {width: 68px; height: 68px;}"
                        "</style>"
                        "<div class='icon'><div><div>"
                        "</div></div></div>"
                        "</div>"));

    html.append("<div class='b-tooltip_body'>");

    if (!sRank.isEmpty())
        sName.append(QString(" (%0)").arg(sRank));

    html.append(QString("<b>Id:</b> %0<br />")
        .arg(spellInfo->id));

    html.append(QString("<b>Name:</b> %0<br />")
        .arg(sName));

    if (!sDescription.isEmpty())
        html.append(QString("<b>Description:</b> %0<br />").arg(getDescription(sDescription, spellInfo)));

    if (!sToolTip.isEmpty())
        html.append(QString("<b>ToolTip:</b> %0<br />").arg(getDescription(sToolTip, spellInfo)));

    html.append("</div>");

    quint32 parentId = getParentSpellId(spellInfo->id);
    if (parentId)
    {
        if (const Spell::entry* parentInfo = Spell::getRecord(parentId, true))
        {
            QString sParentName(parentInfo->name());
            QString sParentRank(parentInfo->rank());

            if (!sParentRank.isEmpty())
                sParentName.append(" (" + sParentRank + ")");

            html.append(QString("<div class='b-vlink'><b>Parent spell:</b> <a href='http://spellwork/%0' class='blue_link'>%0 - %1</a></div>")
                .arg(parentId)
                .arg(sParentName));
        }
    }

    html.append("<div class='b-box-title'>General info</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>"
                "<ul>");

     if (spellInfo->modalNextSpell)
        html.append(QString("<li>ModalNextSpell: %0</li>")
            .arg(spellInfo->modalNextSpell));

    html.append(QString("<li>Category = %0, SpellIconId = %1, ActiveIconId = %2, SpellVisual = (%3, %4)</li>")
        .arg(spellInfo->category)
        .arg(spellInfo->spellIconId)
        .arg(spellInfo->activeIconId)
        .arg(spellInfo->spellVisual[0])
        .arg(spellInfo->spellVisual[1]));

    html.append(QString("<li>SpellFamilyName = %0, SpellFamilyFlags = 0x%1</li>")
        .arg(m_enums->getSpellFamilies()[spellInfo->spellFamilyName])
        .arg(sSpellFamilyFlags.toUpper()));

    html.append(QString("<li>SpellSchool = %0 (%1)</li>")
        .arg(spellInfo->school)
        .arg(m_enums->getSchools()[spellInfo->school]));

    html.append(QString("<li>DamageClass = %0 (%1)</li>")
        .arg(spellInfo->damageClass)
        .arg(m_enums->getDamageClasses()[spellInfo->damageClass]));

    html.append(QString("<li>PreventionType = %0 (%1)</li>")
        .arg(spellInfo->preventionType)
        .arg(m_enums->getPreventionTypes()[spellInfo->preventionType]));

    html.append("</ul></div></div>");

    if (spellInfo->attributes || spellInfo->attributesEx1 || spellInfo->attributesEx2 ||
        spellInfo->attributesEx3 || spellInfo->attributesEx4)
    {
        html.append("<div class='b-box-title'>Attributes</div>"
                    "<div class='b-box-body'>"
                    "<div class='b-box'>"
                    "<ul>");

        if (spellInfo->attributes)
            html.append(QString("<li>Attributes: 0x%0 (%1)</li>")
                .arg(sAttributes.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR)));

        if (spellInfo->attributesEx1)
            html.append(QString("<li>AttributesEx1: 0x%0 (%1)</li>")
                .arg(sAttributesEx1.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX1)));

        if (spellInfo->attributesEx2)
            html.append(QString("<li>AttributesEx2: 0x%0 (%1)</li>")
                .arg(sAttributesEx2.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX2)));

        if (spellInfo->attributesEx3)
            html.append(QString("<li>AttributesEx3: 0x%0 (%1)</li>")
                .arg(sAttributesEx3.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX3)));

        if (spellInfo->attributesEx4)
            html.append(QString("<li>AttributesEx4: 0x%0 (%1)</li>")
                .arg(sAttributesEx4.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ATTR_EX4)));

        html.append("</ul>"
	                "</div>"
                    "</div>");
    }

    html.append("<div class='b-box-title'>Advanced info</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>"
                "<ul>");

    if (spellInfo->targets)
        html.append(QString("<li>Targets Mask = 0x%0 (%1)</li>")
            .arg(sTargetMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_TARGETS)));

    if (spellInfo->targetCreatureType)
        html.append(QString("<li>Creature Type Mask = 0x%0 (%1)</li>")
            .arg(sCreatureTypeMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_CREATURE)));

    if (spellInfo->stances)
        html.append(QString("<li>Stances: 0x%0 (%1)</li>")
            .arg(sFormMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS)));

    if (spellInfo->stancesNot)
        html.append(QString("<li>Stances not: 0x%0 (%1)</li>")
            .arg(sFormMask.toUpper())
            .arg(containAttributes(spellInfo, TYPE_FORMS_NOT)));

    appendSkillInfo(spellInfo);
    html.append(QString("<li>Spell Level = %0, BaseLevel %1, MaxLevel %2, MaxTargetLevel %3</li>")
        .arg(spellInfo->spellLevel)
        .arg(spellInfo->baseLevel)
        .arg(spellInfo->maxLevel)
        .arg(spellInfo->maxTargetLevel));

    if (spellInfo->equippedItemClass != -1)
    {
        html.append(QString("<li>EquippedItemClass = %0 (%1)</li>")
            .arg(spellInfo->equippedItemClass)
            .arg(m_enums->getItemClasses()[spellInfo->equippedItemClass]));

        if (spellInfo->equippedItemSubClassMask)
        {
            html.append("<ul>");
            QString sItemSubClassMask(QString("%0").arg(spellInfo->equippedItemSubClassMask, 8, 16, QChar('0')));
            switch (spellInfo->equippedItemClass)
            {
                case 2: // WEAPON
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_WEAPON)));
                    break;
                case 4: // ARMOR
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_ARMOR)));
                    break;
                case 15: // MISC
                html.append(QString("<li>SubClass mask 0x%0 (%1)</li>")
                    .arg(sItemSubClassMask.toUpper())
                    .arg(containAttributes(spellInfo, TYPE_ITEM_MISC)));
                    break;
            }

            html.append("</ul>");
        }

        if (spellInfo->equippedItemInventoryTypeMask)
        {
            QString sItemInventoryMask(QString("%0").arg(spellInfo->equippedItemInventoryTypeMask, 8, 16, QChar('0')));
            html.append(QString("<li>InventoryType mask = 0x%0 (%1)</li>")
                .arg(sItemInventoryMask.toUpper())
                .arg(containAttributes(spellInfo, TYPE_ITEM_INVENTORY)));
        }
    }

    html.append(QString("<li>Category = %0</li>")
        .arg(spellInfo->category));

    html.append(QString("<li>DispelType = %0 (%1)</li>")
        .arg(spellInfo->dispel)
        .arg(m_enums->getDispelTypes()[spellInfo->dispel]));

    html.append(QString("<li>Mechanic = %0 (%1)</li>")
        .arg(spellInfo->mechanic)
        .arg(m_enums->getMechanics()[spellInfo->mechanic]));

    appendRangeInfo(spellInfo);

    if (spellInfo->speed)
        html.append(QString("<li>Speed: %0</li>")
            .arg(spellInfo->speed, 0, 'f', 2));

    if (spellInfo->stackAmount)
        html.append(QString("<li>Stackable up to %0</li>")
            .arg(spellInfo->stackAmount));

    appendCastTimeInfo(spellInfo);

    if (spellInfo->recoveryTime || spellInfo->categoryRecoveryTime || spellInfo->startRecoveryCategory)
    {
        html.append(QString("<li>RecoveryTime: %0 ms, CategoryRecoveryTime: %1 ms</li>")
            .arg(spellInfo->recoveryTime)
            .arg(spellInfo->categoryRecoveryTime));

        html.append(QString("<li>StartRecoveryCategory = %0, StartRecoveryTime = %1 ms</li>")
            .arg(spellInfo->startRecoveryCategory)
            .arg(float(spellInfo->startRecoveryTime), 0, 'f', 2));
    }

    appendDurationInfo(spellInfo);

    if (spellInfo->manaCost || spellInfo->manaCostPercentage)
    {
        if (spellInfo->manaCost)
        {
            html.append(QString("<li>Power Type = %0, Cost %1")
                .arg(m_enums->getPowers()[spellInfo->powerType])
                .arg(spellInfo->manaCost));
        }
        else if (spellInfo->manaCostPercentage)
        {
            html.append(QString("<li>Power Type = %0, Cost %1% of base mana")
                .arg(m_enums->getPowers()[spellInfo->powerType])
                .arg(spellInfo->manaCostPercentage));
        }

        if (spellInfo->manaCostPerlevel)
            html.append(QString(" + lvl * %0")
                .arg(spellInfo->manaCostPerlevel));

        if (spellInfo->manaPerSecond)
            html.append(QString(" + %0 Per Second")
                .arg(spellInfo->manaPerSecond));

        if (spellInfo->manaPerSecondPerLevel)
            html.append(QString(" + lvl * %0")
                .arg(spellInfo->manaPerSecondPerLevel));

        html.append("</li>");
    }

    html.append(QString("<li>Interrupt Flags: 0x%0, AuraIF 0x%1, ChannelIF 0x%2</li>")
        .arg(sIF.toUpper())
        .arg(sAIF.toUpper())
        .arg(sCIF.toUpper()));

    if (spellInfo->casterAuraState)
        html.append(QString("<li>CasterAuraState = %0 (%1)</li>")
            .arg(spellInfo->casterAuraState)
            .arg(m_enums->getAuraStates()[spellInfo->casterAuraState]));

    if (spellInfo->targetAuraState)
        html.append(QString("<li>TargetAuraState = %0 (%1)</li>")
            .arg(spellInfo->targetAuraState)
            .arg(m_enums->getAuraStates()[spellInfo->targetAuraState]));

    if (spellInfo->requiresSpellFocus)
        html.append(QString("<li>Requires Spell Focus %0</li>")
            .arg(spellInfo->requiresSpellFocus));

    if (spellInfo->procFlags)
    {
        QString sProcFlags(QString("%0").arg(spellInfo->procFlags, 8, 16, QChar('0')));
        html.append(QString("<li><b>Proc flag 0x%0, chance = %1, charges - %2</b></li>")
            .arg(sProcFlags.toUpper())
            .arg(spellInfo->procChance)
            .arg(spellInfo->procCharges));

        appendProcInfo(spellInfo);
    }
    else
    {
        html.append(QString("<li>Chance = %0, charges - %1</li>")
            .arg(spellInfo->procChance)
            .arg(spellInfo->procCharges));
    }

    html.append("</ul></div></div>");

    appendSpellEffectInfo(spellInfo);

    html.append("</body></html>");

    // Formatting for debug
    html.replace("><", ">\n<");

    browser->setHtml(html, QUrl(QString("http://spellwork/%0").arg(spellInfo->id)));
    //browser->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

void SWObject::appendRangeInfo(Spell::entry const* spellInfo)
{
    if (const SpellRange::entry* range = SpellRange::getRecord(spellInfo->rangeIndex, true))
    {
        html.append(QString("<li>SpellRange (Id %0) \"%1\"</li>"
                            "<ul><li>MinRange = %2</li>"
                            "<li>MaxRange = %3</li></ul>")
            .arg(range->id)
            .arg(range->name())
            .arg(range->minRange)
            .arg(range->maxRange));
    }
}

void SWObject::appendProcInfo(Spell::entry const* spellInfo)
{
    quint8 i = 0;
    quint64 proc = spellInfo->procFlags;

    html.append("<ul>");
    while (proc != 0)
    {
        if ((proc & 1) != 0)
            html.append(QString("<li>%0</li>").arg(ProcFlagDesc[i]));
        ++i;
        proc >>= 1;
    }
    html.append("</ul>");
}

void SWObject::appendSpellEffectInfo(Spell::entry const* spellInfo)
{
    html.append("<div class='b-box-title'>Effects</div>"
                "<div class='b-box-body'>"
                "<div class='b-box'>");

    for (quint8 eff = 0; eff < MAX_EFFECT_INDEX; ++eff)
    {
        if (!spellInfo->effect[eff])
        {
            html.append(QString("<div class='b-effect_name'>Effect %0:</div>"
                                "<ul>"
		                        "<li>NO EFFECT</li>"
		                        "</ul>").arg(eff));
        }
        else
        {
            QString _BasePoints(QString("<li>BasePoints = %0").arg(spellInfo->effectBasePoints[eff] + 1));

            QString _RealPoints;
            if (spellInfo->effectRealPointsPerLevel[eff] != 0)
                _RealPoints = QString(" + Level * %0").arg(spellInfo->effectRealPointsPerLevel[eff], 0, 'f', 2);

            QString _DieSides;
            if (1 < spellInfo->effectDieSides[eff])
            {
                if (spellInfo->effectRealPointsPerLevel[eff] != 0)
                    _DieSides = QString(" to %0 + lvl * %1")
                        .arg(spellInfo->effectBasePoints[eff] + 1 + spellInfo->effectDieSides[eff])
                        .arg(spellInfo->effectRealPointsPerLevel[eff], 0, 'f', 2);
                else
                    _DieSides = QString(" to %0").arg(spellInfo->effectBasePoints[eff] + 1 + spellInfo->effectDieSides[eff]);
            }

            QString _PointsPerCombo;
            if (spellInfo->effectPointsPerComboPoint[eff] != 0)
                _PointsPerCombo = QString(" + combo * %0").arg(spellInfo->effectPointsPerComboPoint[eff], 0, 'f', 2);

            QString _DamageMultiplier;
            if (spellInfo->damageMultiplier[eff] != 1.0f)
                _DamageMultiplier = QString(" * %0").arg(spellInfo->damageMultiplier[eff], 0, 'f', 2);

            QString _Multiple;
            if (spellInfo->effectMultipleValue[eff] != 0)
                _Multiple = QString(", Multiple = %0").arg(spellInfo->effectMultipleValue[eff], 0, 'f', 2);

            QString _Result = _BasePoints + _RealPoints + _DieSides + _PointsPerCombo + _DamageMultiplier + _Multiple + "</li>";

            html.append(QString("<div class='b-effect_name'>Effect %0:</div>"
                                "<ul>").arg(eff));

            html.append(QString("<li>Id: %0 (%1)</li>")
                .arg(spellInfo->effect[eff])
                .arg(m_enums->getSpellEffects()[spellInfo->effect[eff]]));

            html.append(_Result);

            html.append(QString("<li>Targets (%0, %1) (%2, %3)</li>")
                .arg(spellInfo->effectImplicitTargetA[eff])
                .arg(spellInfo->effectImplicitTargetB[eff])
                .arg(m_enums->getTargets()[spellInfo->effectImplicitTargetA[eff]])
                .arg(m_enums->getTargets()[spellInfo->effectImplicitTargetB[eff]]));

            appendAuraInfo(spellInfo, eff);

            appendRadiusInfo(spellInfo, eff);

            appendTriggerInfo(spellInfo, eff);

            if (spellInfo->effectChainTarget[eff] != 0)
                html.append(QString("<li>EffectChainTarget = %0</li>").arg(spellInfo->effectChainTarget[eff]));

            if (spellInfo->effectMechanic[eff] != 0)
            {
                html.append(QString("<li>Effect Mechanic = %0 (%1)</li>")
                    .arg(spellInfo->effectMechanic[eff])
                    .arg(m_enums->getMechanics()[spellInfo->effectMechanic[eff]]));
            }

            if (spellInfo->effectItemType[eff] != 0)
            {
                QString sEffectItemType(QString("%0").arg(spellInfo->effectItemType[eff], 8, 16, QChar('0')));
                html.append(QString("<li>EffectItemType = 0x%0</li>").arg(sEffectItemType.toUpper()));

                if (spellInfo->effect[eff] == 6)
                {
                    html.append("<ul>");
                    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
                    {
                        if (const Spell::entry* t_spellInfo = Spell::getRecord(i))
                        {
                            bool hasSkill = false;
                            if ((t_spellInfo->spellFamilyName == spellInfo->spellFamilyName) &&
                                (t_spellInfo->spellFamilyFlags & spellInfo->effectItemType[eff]))
                            {
                                QString sName(t_spellInfo->name());
                                QString sRank(t_spellInfo->rank());

                                if (!sRank.isEmpty())
                                    sName.append(" (" + sRank + ")");

                                for (quint32 sk = 0; sk < SkillLineAbility::getHeader()->recordCount; ++sk)
                                {
                                    const SkillLineAbility::entry* skillInfo = SkillLineAbility::getRecord(sk);
                                    if (skillInfo && skillInfo->spellId == t_spellInfo->id && skillInfo->skillId > 0)
                                    {
                                        hasSkill = true;
                                        html.append(QString("<li><a href='http://spellwork/%1' class='blue_link'>+ %1 - %2</a></li>")
                                            .arg(t_spellInfo->id)
                                            .arg(sName));
                                        break;
                                    }
                                }

                                if (!hasSkill)
                                {
                                    html.append(QString("<li><a href='http://spellwork/%1' class='red_link'>- %1 - %2</a></li>")
                                        .arg(t_spellInfo->id)
                                        .arg(sName));
                                }
                            }
                        }
                    }
                    html.append("</ul>");
                }
            }
            html.append("</ul>");
        }
    }
    html.append("</div></div>");
}

void SWObject::appendTriggerInfo(Spell::entry const* spellInfo, quint8 index)
{
    quint32 trigger = spellInfo->effectTriggerSpell[index];
    if (trigger != 0)
    {
        if (const Spell::entry* triggerSpell = Spell::getRecord(trigger, true))
        {
            QString sName(triggerSpell->name());
            QString sRank(triggerSpell->rank());

            if (!sRank.isEmpty())
                sName.append(" (" + sRank + ")");

            html.append(QString("<li><b>Trigger spell:</b> <a href='http://spellwork/%0' class='blue_link'>%0 - %1</a>. Chance = %2</li>")
                .arg(trigger)
                .arg(sName)
                .arg(triggerSpell->procChance));

                QString sDescription(triggerSpell->description());
                QString sTooltip(triggerSpell->toolTip());

                html.append("<ul>");

                if (!sDescription.isEmpty())
                    html.append(QString("<li>Description: %0</li>").arg(getDescription(sDescription, triggerSpell)));

                if (!sTooltip.isEmpty())
                    html.append(QString("<li>ToolTip: %0</li>").arg(getDescription(sTooltip, triggerSpell)));

                if (triggerSpell->procFlags != 0)
                {
                    html.append(QString("<li>Charges - %0</li>").arg(triggerSpell->procCharges));
                    html.append("<hr style='margin: 0 25px;'>");
                    appendProcInfo(triggerSpell);
                }

                html.append("</ul>");
        }
        else
        {
            html.append(QString("<li>Trigger spell: %0 Not found</li>").arg(trigger));
        }
    }
}

void SWObject::appendRadiusInfo(Spell::entry const* spellInfo, quint8 index)
{
    quint16 rIndex = spellInfo->effectRadiusIndex[index];
    if (rIndex != 0)
    {
        if (const SpellRadius::entry* spellRadius = SpellRadius::getRecord(rIndex, true))
        {
            html.append(QString("<li>Radius (Id %0) %1</li>")
                .arg(rIndex)
                .arg(spellRadius->radius, 0, 'f', 2));
        }
        else
            html.append(QString("<li>Radius (Id %0) Not found</li>").arg(rIndex));
    }
}

void SWObject::appendAuraInfo(Spell::entry const* spellInfo, quint8 index)
{
    QString sAura(m_enums->getSpellAuras()[spellInfo->effectApplyAuraName[index]]);
    quint32 misc = spellInfo->effectMiscValue[index];

    if (spellInfo->effectApplyAuraName[index] == 0)
    {
        if (spellInfo->effectMiscValue[index] != 0)
            html.append(QString("<li>EffectMiscValue = %0</li>").arg(spellInfo->effectMiscValue[index]));

        if (spellInfo->effectAmplitude[index] != 0)
            html.append(QString("<li>EffectAmplitude = %0</li>").arg(spellInfo->effectAmplitude[index]));

        return;
    }

    QString _BaseAuraInfo;
    _BaseAuraInfo = QString("<li>Aura Id %0 (%1), value = %2, misc = %3 ")
        .arg(spellInfo->effectApplyAuraName[index])
        .arg(sAura)
        .arg(spellInfo->effectBasePoints[index] + 1)
        .arg(misc);

    QString _SpecialAuraInfo;
    switch (spellInfo->effectApplyAuraName[index])
    {
        case 29:
            _SpecialAuraInfo = QString("(%0").arg(m_enums->getUnitMods()[misc]);
            break;
        case 107:
        case 108:
            _SpecialAuraInfo = QString("(%0").arg(m_enums->getSpellMods()[misc]);
            break;
        // todo: more case
        default:
            _SpecialAuraInfo = QString("(%0").arg(misc);
            break;
    }

    QString _Periodic = QString("), periodic = %0").arg(spellInfo->effectAmplitude[index]);
    QString _Result = _BaseAuraInfo + _SpecialAuraInfo + _Periodic;
    html.append(_Result + "</li>");
}

QString SWObject::containAttributes(Spell::entry const* spellInfo, MaskType type)
{
    QString str("");
    switch (type)
    {
        case TYPE_ATTR:
        {
            EnumIterator itr(m_enums->getAttributes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributes & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX1:
        {
            EnumIterator itr(m_enums->getAttributesEx1());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx1 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX2:
        {
            EnumIterator itr(m_enums->getAttributesEx2());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx2 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX3:
        {
            EnumIterator itr(m_enums->getAttributesEx3());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx3 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ATTR_EX4:
        {
            EnumIterator itr(m_enums->getAttributesEx4());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->attributesEx4 & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_TARGETS:
        {
            EnumIterator itr(m_enums->getTargetFlags());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->targets & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_CREATURE:
        {
            EnumIterator itr(m_enums->getCreatureTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->targetCreatureType & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_FORMS:
        {
            EnumIterator itr(m_enums->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->stances & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_FORMS_NOT:
        {
            EnumIterator itr(m_enums->getShapeshiftForms());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->stancesNot & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_WEAPON:
        {
            EnumIterator itr(m_enums->getItemSubClassWeapons());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_ARMOR:
        {
            EnumIterator itr(m_enums->getItemSubClassArmors());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_MISC:
        {
            EnumIterator itr(m_enums->getItemSubClassMiscs());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemSubClassMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        case TYPE_ITEM_INVENTORY:
        {
            EnumIterator itr(m_enums->getInventoryTypes());
            while (itr.hasNext())
            {
                itr.next();
                if (spellInfo->equippedItemInventoryTypeMask & itr.key())
                {
                    QString tstr(QString("%0, ").arg(itr.value()));
                    str += tstr;
                }
            }
            if (!str.isEmpty())
                str.chop(2);
            return str;
        }
        break;
        default:
        break;
    }
    return str;
}

void SWObject::appendSkillInfo(Spell::entry const* spellInfo)
{
    for (quint32 i = 0; i < SkillLineAbility::getHeader()->recordCount; ++i)
    {
        const SkillLineAbility::entry* skillInfo = SkillLineAbility::getRecord(i);
        if (skillInfo->id && skillInfo->spellId == spellInfo->id)
        {
            if (const SkillLine::entry* skill = SkillLine::getRecord(skillInfo->skillId, true))
            {
                html.append(QString("<li>Skill (Id %0) \"%1\"</li>"
                    "<ul><li>ReqSkillValue = %2</li>"
                    "<li>Forward Spell = %3</li>"
                    "<li>MinMaxValue (%4, %5)</li>"
                    "<li>CharacterPoints (%6, %7)</li></ul>")
                    .arg(skill->id)
                    .arg(skill->name())
                    .arg(skillInfo->requiredSkillValue)
                    .arg(skillInfo->forwardSpellId)
                    .arg(skillInfo->minValue)
                    .arg(skillInfo->maxValue)
                    .arg(skillInfo->charPoints[0])
                    .arg(skillInfo->charPoints[1]));
            }
            else
                html.append(QString("<li>Skill (Id %0) (not found)</li>")
                    .arg(skillInfo->skillId));
            break;
        }
    }
}

void SWObject::appendCastTimeInfo(Spell::entry const* spellInfo)
{
    if (const SpellCastTimes::entry* castInfo = SpellCastTimes::getRecord(spellInfo->castingTimeIndex, true))
    {
        html.append(QString("<li>CastingTime (Id %0) = %1</li>")
            .arg(castInfo->id)
            .arg(float(castInfo->castTime) / 1000, 0, 'f', 2));
    }
}

void SWObject::appendDurationInfo(Spell::entry const* spellInfo)
{
    if (const SpellDuration::entry* durationInfo = SpellDuration::getRecord(spellInfo->durationIndex, true))
    {
        html.append(QString("<li>Duration: ID (%0)  base: %1, per level: %2, max: %3</li>")
            .arg(durationInfo->id)
            .arg(durationInfo->duration)
            .arg(durationInfo->durationPerLevel)
            .arg(durationInfo->maxDuration));
    }
}

void SWObject::compare(bool ok)
{
    if (ok && !m_sourceHtml[1].isEmpty() && !m_sourceHtml[2].isEmpty())
    {
        QStringList list1 = m_sourceHtml[1].split("\n");
        QStringList list2 = m_sourceHtml[2].split("\n");

        QString html1, html2;

        QRegExp rx("(<[A-Za-z_0-9]*>)+([A-Za-z_0-9-!\"#$%&'()*+,./:;=?@[\\]_`{|}~\\s]*)+(</[A-Za-z_0-9]*>)");

        for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
        {
            bool yes = false;

            for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
            {
                if ((*itr1) == (*itr2))
                {
                    yes = true;
                    break;
                }
            }

            if (yes)
            {
                if (rx.indexIn((*itr1)) != -1)
                {
                    // QString r1 = rx.cap(0); // Full
                    QString r2 = rx.cap(1); // <xxx>
                    QString r3 = rx.cap(2); // <>xxx</>
                    QString r4 = rx.cap(3); // </xxx>

                    if (r2 == "<b>")
                        html1.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr1)));
                    else if (r2 == "<style>")
                    {
                        html1.append((*itr1));
                    }
                    else
                    {
                        r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                        r3.prepend(r2);
                        r3.append(r4);
                        html1.append(r3);
                    }
                }
                else
                    html1.append((*itr1));
            }
            else
            {
                if (rx.indexIn((*itr1)) != -1)
                {
                    // QString r1 = rx.cap(0); // Full
                    QString r2 = rx.cap(1); // <xxx>
                    QString r3 = rx.cap(2); // <>xxx</>
                    QString r4 = rx.cap(3); // </xxx>

                    if (r2 == "<b>")
                        html1.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr1)));
                    else if (r2 == "<style>")
                    {
                        html1.append((*itr1));
                    }
                    else
                    {
                        r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                        r3.prepend(r2);
                        r3.append(r4);
                        html1.append(r3);
                    }
                }
                else
                    html1.append((*itr1));
            }
        }

        // second
        for (QStringList::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
        {
            bool yes = false;

            for (QStringList::iterator itr1 = list1.begin(); itr1 != list1.end(); ++itr1)
            {
                if ((*itr2) == (*itr1))
                {
                    yes = true;
                    break;
                }
            }

            if (yes)
            {
                if (rx.indexIn((*itr2)) != -1)
                {
                    // QString r1 = rx.cap(0); // Full
                    QString r2 = rx.cap(1); // <xxx>
                    QString r3 = rx.cap(2); // <>xxx</>
                    QString r4 = rx.cap(3); // </xxx>

                    if (r2 == "<b>")
                        html2.append(QString("<span style='background-color: cyan'>%0</span>").arg((*itr2)));
                    else if (r2 == "<style>")
                    {
                        html2.append((*itr2));
                    }
                    else
                    {
                        r3 = QString("<span style='background-color: cyan'>%0</span>").arg(r3);
                        r3.prepend(r2);
                        r3.append(r4);
                        html2.append(r3);
                    }
                }
                else
                    html2.append((*itr2));
            }
            else
            {
                if (rx.indexIn((*itr2)) != -1)
                {
                    // QString r1 = rx.cap(0); // Full
                    QString r2 = rx.cap(1); // <xxx>
                    QString r3 = rx.cap(2); // <>xxx</>
                    QString r4 = rx.cap(3); // </xxx>

                    if (r2 == "<b>")
                        html2.append(QString("<span style='background-color: salmon'>%0</span>").arg((*itr2)));
                    else if (r2 == "<style>")
                    {
                        html2.append((*itr2));
                    }
                    else
                    {
                        r3 = QString("<span style='background-color: salmon'>%0</span>").arg(r3);
                        r3.prepend(r2);
                        r3.append(r4);
                        html2.append(r3);
                    }
                }
                else
                    html2.append((*itr2));
            }
        }

        m_form->webView2->setHtml(html1, m_form->webView2->url());
        m_form->webView3->setHtml(html2, m_form->webView3->url());
        m_sourceHtml[1].clear();
        m_sourceHtml[2].clear();
    }
    else
    {
        if (m_sourceHtml[1].isEmpty())
        {
            m_form->webView2->page()->toHtml([this](const QString &result)
            {
                this->m_sourceHtml[1] = result;
                this->compare(true);
            });
        }
        if (m_sourceHtml[2].isEmpty())
        {
            m_form->webView3->page()->toHtml([this](const QString &result)
            {
                this->m_sourceHtml[2] = result;
                this->compare(true);
            });
        }
    }
}

quint64 Converter::getULongLong(QString value)
{
    bool ok;
    quint64 dec = value.toULongLong(&ok, 10);
    return ok ? dec : value.toULongLong(&ok, 16);
}

qint64 Converter::getLongLong(QString value)
{
    bool ok;
    qint64 dec = value.toLongLong(&ok, 10);
    return ok ? dec : value.toLongLong(&ok, 16);
}

quint32 Converter::getULong(QString value)
{
    bool ok;
    quint32 dec = value.toULong(&ok, 10);
    return ok ? dec : value.toULong(&ok, 16);
}

qint32 Converter::getLong(QString value)
{
    bool ok;
    qint32 dec = value.toLong(&ok, 10);;
    return ok ? dec : value.toLong(&ok, 16);
}
