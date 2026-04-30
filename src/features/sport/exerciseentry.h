#ifndef EXERCISEENTRY_H
#define EXERCISEENTRY_H

#include <QString>

class ExerciseEntry
{
public:
    ExerciseEntry();
    ExerciseEntry(int pId, QString pName, QString pMuscleGroup);

    int getId() const noexcept;
    const QString& getName() const noexcept;
    const QString& getMuscleGroup() const noexcept;

    void setId(int pId);
    void setName(QString pName);
    void setMuscleGroup(QString pMuscleGroup);

private:
    int mId;
    QString mName;
    QString mMuscleGroup;
};

#endif // EXERCISEENTRY_H
