#ifndef BOOKS__H
#define BOOKS__H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Books : public Controller
{
 Q_OBJECT
public:
 explicit Books(QObject *parent = nullptr);
 ~Books();

 C_ATTR(index, :Path :AutoArgs)
 void index(Context* c);

 C_ATTR(list, :Local)
 void list(Context* c);

 C_ATTR(ok, :Local)
 void ok(Context* c);

};

#endif //BOOKS__H

