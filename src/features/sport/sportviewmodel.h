#ifndef SPORTVIEWMODEL_H
#define SPORTVIEWMODEL_H

#include <QObject>
#include <QVariantList>

#include "sportservice.h"

class SportViewModel final : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString searchText READ getSearchText WRITE setSearchText NOTIFY searchTextChanged FINAL)
    Q_PROPERTY(QString selectedMuscleGroup READ getSelectedMuscleGroup WRITE setSelectedMuscleGroup NOTIFY selectedMuscleGroupChanged FINAL)
    Q_PROPERTY(QVariantList filteredExercises READ getFilteredExercises NOTIFY filteredExercisesChanged FINAL)

public:
    explicit SportViewModel(SportService* pService, QObject* pParent = nullptr);

    QString getSearchText() const;
    void setSearchText(const QString& pSearchText);

    QString getSelectedMuscleGroup() const;
    void setSelectedMuscleGroup(const QString& pMuscleGroup);

    QVariantList getFilteredExercises() const;

    Q_INVOKABLE void clearExerciseFilters();

signals:
    void searchTextChanged();
    void selectedMuscleGroupChanged();
    void filteredExercisesChanged();

private:
    void wireSignals();

    SportService* mService = nullptr;
};

#endif // SPORTVIEWMODEL_H
