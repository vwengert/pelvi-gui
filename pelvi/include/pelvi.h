#pragma once

#include <QObject>
#include "export.h"

class PImpl;

class EXPORT Pelvi : public QObject
{
    Q_OBJECT

  public:
    explicit Pelvi( QObject* parent = nullptr );
    ~Pelvi();

  private:
    PImpl* m_pimpl;
};
