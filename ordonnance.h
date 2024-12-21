#ifndef ORDONNANCE_H
#define ORDONNANCE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Ordonnance
{
    int IdPre;
    QString Reference;
    QString DrName;
    QString Instructions;

public:
    // Default constructor
    Ordonnance() {}

    // Constructor with parameters
    Ordonnance(int, QString, QString, QString);

    // Getters
    int getIdPre() const { return IdPre; }
    QString getReference() const { return Reference; }
    QString getDrName() const { return DrName; }
    QString getInstructions() const { return Instructions; }

    // Setters
    void setIdPre(int id) { IdPre = id; }
    void setReference(const QString &ref) { Reference = ref; }
    void setDrName(const QString &name) { DrName = name; }
    void setInstructions(const QString &instr) { Instructions = instr; }

    // Database operations
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int IdPre);
    QSqlQueryModel* display();
    bool modifier();
    QMap<QString, int> Statistics();
};

#endif // ORDONNANCE_H
