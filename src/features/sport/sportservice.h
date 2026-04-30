#ifndef SPORTSERVICE_H
#define SPORTSERVICE_H

#include <QObject>
#include <QVariantList>

#include "sportrepository.h"

class SportService final : public QObject
{
    Q_OBJECT

public:
    explicit SportService(DatabaseManager* pDatabaseManager, QObject* pParent = nullptr);

    bool ensureDefaultExercises();

    QString getSearchText() const;
    void setSearchText(const QString& pSearchText);

    QString getSelectedMuscleGroup() const;
    void setSelectedMuscleGroup(const QString& pMuscleGroup);

    QVariantList filteredExercises() const;

signals:
    void filtersChanged();
    void exercisesChanged();

private:
    SportRepository mRepository;
    QString mSearchText;
    QString mSelectedMuscleGroup;
};

#endif // SPORTSERVICE_H
