// Copyright (c) 2022 Manuel Schneider

#pragma once
#include "albert/extension.h"
#include "iconprovider.h"
#include <QAbstractListModel>
#include <QIcon>
#include <map>
#include <memory>
#include <vector>
namespace albert{ class Item; class RankItem; }

class ItemsModel : public QAbstractListModel
{
    Q_OBJECT
public:

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void add(albert::Extension*, const std::shared_ptr<albert::Item>&);
    void add(albert::Extension*, std::shared_ptr<albert::Item>&&);

    void add(albert::Extension*, const std::vector<std::shared_ptr<albert::Item>>&);
    void add(albert::Extension*, std::vector<std::shared_ptr<albert::Item>>&&);

    void add(std::vector<std::pair<albert::Extension*,albert::RankItem>>::iterator begin,
             std::vector<std::pair<albert::Extension*,albert::RankItem>>::iterator end);

    QAbstractListModel *buildActionsModel(uint i) const;
    void activate(uint i, uint a);

    static void clearIconCache();

private:
    std::vector<std::pair<albert::Extension*,std::shared_ptr<albert::Item>>> items;
    static IconProvider icon_provider;
    static std::map<std::pair<QString,QString>, QIcon> icon_cache;

signals:
    void activated(const QString &extension_id,
                   const QString &item_id,
                   const QString &action_id);
};
