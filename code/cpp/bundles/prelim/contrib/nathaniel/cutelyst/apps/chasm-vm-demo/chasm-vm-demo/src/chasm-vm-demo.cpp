#include "chasm-vm-demo.h"

#include "chasm-info.h"

#include "test-controller.h"

#include "root.h"

#include "Cutelyst/Plugins/View/Grantlee/grantleeview.h"

#include "Cutelyst/tsi/chasm-view.h"
USING_CHASM_NAMESPACE


using namespace Cutelyst;

Chasm_VM_Demo::Chasm_VM_Demo(QObject *parent) : Application(parent)
{
}

Chasm_VM_Demo::~Chasm_VM_Demo()
{
}

bool Chasm_VM_Demo::init()
{
 new Root(this);
 new Chasm_Info(this);
 new Test_Controller(this);

 chasm_view_ = new Chasm_View(this);
 chasm_view_->set_include_paths({ pathTo("root/src") });


 // //  note: no controllers depending on this view will
  //    be found by default, because it is not the first
  //    view created; instead, explicitly invoke this
  //    view when other views are not suitable for a
  //    particular path or controller ...
 grantlee_view_ = new GrantleeView(this);
 grantlee_view_->setIncludePaths({ pathTo("root/src") });


 chasm_view_->alternative_views().push_back(grantlee_view_);
 return true;
}

