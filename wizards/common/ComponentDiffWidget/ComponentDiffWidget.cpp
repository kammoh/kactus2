//-----------------------------------------------------------------------------
// File: ComponentDiffWidget.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 17.10.2014
//
// Description:
// Tree widget for displaying differences of two components.
//-----------------------------------------------------------------------------

#include "ComponentDiffWidget.h"

#include <IPXACTmodels/component.h>

#include <wizards/common/ComponentComparator/ComponentComparator.h>

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::ComponentDiffWidget()
//-----------------------------------------------------------------------------
ComponentDiffWidget::ComponentDiffWidget(QWidget *parent)
    : QTreeWidget (parent)
{
    QStringList labels;
    labels << "Name" << "Changed element" << "Previous value" << "Updated value";
    setHeaderLabels(labels);

    setColumnCount(labels.count());    
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::~ComponentDiffWidget()
//-----------------------------------------------------------------------------
ComponentDiffWidget::~ComponentDiffWidget()
{

}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::setComponents()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::setComponents(QSharedPointer<const Component> reference, 
    QSharedPointer<const Component> subject)
{
    clear();

    ComponentComparator comparator;
    QList<QSharedPointer<IPXactDiff> > diffs = comparator.diff(reference, subject);

    if (diffs.count() == 1 && diffs.first()->changeType() == IPXactDiff::NO_CHANGE)
    {
        return;
    }

    QStringList topElements;
    topElements << "view" << "model parameter";

    QMap<QString, QTreeWidgetItem*> topItems;
    
    foreach(QSharedPointer<IPXactDiff> diff, diffs)
    {
        if (topElements.contains(diff->element()) && !topItems.contains(diff->element()))
        {
            QTreeWidgetItem* item = new QTreeWidgetItem();
            QString containerName = diff->element().at(0).toUpper() + diff->element().mid(1) + "s";
            item->setText(ITEM_NAME, containerName);
            addTopLevelItem(item);
            topItems.insert(diff->element(), item);
        }
    }

    foreach(QSharedPointer<IPXactDiff> diff, diffs)
    {
        QTreeWidgetItem* parentItem = topItems.value(diff->element());

        if (diff->changeType() == IPXactDiff::ADD)
        {    
            addAddItem(diff->name(), parentItem);
        }
        else if (diff->changeType() == IPXactDiff::REMOVE)
        {    
            addRemoveItem(diff->name(), parentItem);
        }
        else if (diff->changeType() == IPXactDiff::MODIFICATION)
        {              
            addModificationItem(diff, parentItem);
        }
    }
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::createAddItem()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::addAddItem(QString const& name, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* addItem = new QTreeWidgetItem(parent);
    addItem->setText(ITEM_NAME, name);
    addItem->setIcon(ITEM_NAME, QIcon(":/icons/common/graphics/add.png"));
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::createRemoveItem()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::addRemoveItem(QString const& name, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* removeItem = new QTreeWidgetItem(parent);
    removeItem->setText(ITEM_NAME, name);
    removeItem->setIcon(ITEM_NAME, QIcon(":/icons/common/graphics/remove.png"));
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::addModificationItem()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::addModificationItem(QSharedPointer<IPXactDiff> diff, QTreeWidgetItem* parent)
{
    QList<IPXactDiff::Modification> changelist = diff->getChangeList();
    if (changelist.size() == 1)
    {                       
        addSingleLevelModificationItem(diff->name(), changelist.first(), parent);
    }
    else
    {
        addMultiLevelModificationItem(diff->name(), changelist, parent);
    }
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::createSingleLevelModificationItem()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::addSingleLevelModificationItem(QString const& name, 
    IPXactDiff::Modification const& modification, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* modificationItem = createModificationItem(modification, parent);
    modificationItem->setText(ITEM_NAME, name);  
    modificationItem->setIcon(ITEM_NAME, QIcon(":/icons/common/graphics/asterisk-yellow.png"));
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::createModificationItem()
//-----------------------------------------------------------------------------
QTreeWidgetItem* ComponentDiffWidget::createModificationItem(IPXactDiff::Modification const& modification, 
    QTreeWidgetItem* parent) const
{
    QTreeWidgetItem* modificationItem = new QTreeWidgetItem(parent);
    modificationItem->setText(CHANGE_ELEMENT, modification.modifiedElement);
    modificationItem->setText(PREVIOUS_VALUE, modification.previousValue);
    modificationItem->setText(UPDATED_VALUE, modification.newValue);

    return modificationItem;
}

//-----------------------------------------------------------------------------
// Function: ComponentDiffWidget::createMultiLevelModificationItem()
//-----------------------------------------------------------------------------
void ComponentDiffWidget::addMultiLevelModificationItem(QString const& name, 
    QList<IPXactDiff::Modification> changelist, QTreeWidgetItem* parent)
{
    QTreeWidgetItem* child = new QTreeWidgetItem(parent);
    child->setText(ITEM_NAME, name);  
    child->setIcon(ITEM_NAME, QIcon(":/icons/common/graphics/asterisk-yellow.png"));
    child->setText(CHANGE_ELEMENT, "[multiple changes]");

    foreach(IPXactDiff::Modification modification, changelist)
    {
        child->addChild(createModificationItem(modification, child));
    }
}
