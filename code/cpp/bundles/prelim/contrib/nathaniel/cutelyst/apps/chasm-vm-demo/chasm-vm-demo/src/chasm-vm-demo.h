#ifndef CHASM_VM_DEMO__H
#define CHASM_VM_DEMO__H


         #define _including_from_app_
#include <Cutelyst/Application>
         #undef _including_from_app_


using namespace Cutelyst;


namespace_class(Cutelyst ,GrantleeView)
namespace_class(Chasm::TSI ,Chasm_View)

#include "Cutelyst/tsi/chasm-macros.h"
USING_CHASM_NAMESPACE


class Chasm_VM_Demo : public Application
{
 Q_OBJECT
 CUTELYST_APPLICATION(IID "chasm_vm_demo")

public:
 Q_INVOKABLE explicit Chasm_VM_Demo(QObject *parent = nullptr);
 ~Chasm_VM_Demo();

 Chasm_View* chasm_view_;
 GrantleeView* grantlee_view_;

 bool init();
};

#endif //CHASM_VM_DEMO__H

