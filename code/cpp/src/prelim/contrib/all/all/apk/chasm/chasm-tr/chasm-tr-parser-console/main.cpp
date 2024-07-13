

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)




#include "textio.h"

USING_KANS(TextIO)


/*

<! <x>[retval] <\ [proc](pr)  [lambda](<*>[retval] <\ [proc](add) [lambda](5 7) ) !>

.,
load-pst $ /test ;.
,.

,x int

.<x>[r] [p](pr)  [l](<*>[r] [p](add) [l](5 7) )

.[p](unless) [l]($1 $2) = .[p](if) [l](<*>[r] [l](;1) ;2)


[p] = %
[r] = @
[l] = \
[m] = &
[s] =
[e] =
[c] = @.

.<x>@ %(pr) \(<*>@ %(add) \(5 7) )


.&(unless) \($1 $2) = .%(if) \(<*>@ \(;1) ;2)


.<x>@. %(test) \+(this)


.<x>[c]

 */

#include "chasm-tr-parser/chtr-document.h"

#include "chasm-tr/chvm/chvm-code-generator.h"
//?#include "chasm-tr/chvm/eval/channel-package-runner.h"


USING_AQNS(Chasm_TR)

//#include "ch




#include "chasm-lib/chasm/chasm-runtime.h"
//#include "chasm-lib/chasm/chasm-call-package.h"

#include "chasm-vm/chasm-vm.h"
#include "chasm-runtime-bridge/chasm-runtime-bridge.h"
#include "chasm-procedure-table/chasm-procedure-table.h"

#include "chasm-chgr/chgr-environment.h"
#include "chasm-chgr/chgr-hypernode.h"


void testqvar(QVariant arg1, r8 arg2, u2 arg3)
{
 qDebug() << "arg1 = " << arg1;
 qDebug() << "arg2 = " << arg2;
 qDebug() << "arg3 = " << arg3;
}

void prn(u1 arg1)
{
 qDebug() << "arg1 = " << arg1;
}

void prs(QString arg1)
{
 qDebug() << "arg1 = " << arg1;
}

void demo_opencv(QString arg1)
{
 qDebug() << "arg1: = " << arg1;

}


void allocate_hypernode(u4& id)
{
 ChGr_Environment::allocate_new_hypernode(id);
 qDebug() << "id = " << id;
}


void allocate_mempad(u4& id, u4 size)
{
 ChGr_Environment::allocate_new_mempad(id, size);
 qDebug() << "id = " << id << "and size = " << size;
}




int main2(int argc, char *argv[])
{
 QVector<QVector<QString>> links {

  {"app.com", "Asbury Park Press (Asbury Park, NJ)", "biden-app"},
  {"northjersey.com", "The Bergen Record (Woodland Park, NJ)", "biden-bergen"},
  {"pressconnects.com", "Binghamton Press Connects (Binghamton, NY)", "biden-press-connects"},
  {"burlingtoncountytimes.com", "Burlington County Times (Westampton, NJ)", "biden-burlington"},
  {"mycentraljersey.com", "Central New Jersey News (Somerville, NJ)", "biden-cnj"},
  {"publicopiniononline.com", "Chambersburg Public Opinion (Chambersburg, PA)", "biden-public-opinion"},
  {"the-leader.com", "The Corning Leader (Corning, NY))", "biden-leader"},
  {"thedailyjournal.com", "The Daily Journal (Vineland, NJ)", "biden-dj"},
  {"mpnnow.com", "Daily Messenger (Canandaigua, NY)", "biden-daily-messenger"},
  {"echo-pilot.com", "Echo Pilot (Greencastle, PA)", "biden-echo"},
  {"eveningsun.com", "Hanover Evening Sun (Hanover, PA)", "biden-eve-sun"},
  {"ithacajournal.com", "Ithaca Journal (Ithaca, NY)", "biden-ithaca"},
  {"lohud.com", "The Journal News | lohud.com (Westchester County and Rockland County, NY)", "biden-lohud"},
  {"ldnews.com", "Lebanon Daily News (Lebanon, PA)", "biden-lebanon"},
  {"poconorecord.com", "Pocono Record (Stroudsburg, PA)", "biden-pocono"},
  {"poughkeepsiejournal.com", "The Poughkeepsie Journal (Poughkeepsie, NY)", "biden-poughkeepsie"},
  {"stargazette.com", "Star Gazette (Elmira, NY)", "biden-star"},
  {"recordonline.com", "Times Herald-Record (Middletown, NY)", "biden-thr"},
  {"timestelegram.com", "The Times Telegram (Herkimer, NY)", "biden-times-telegram"},
  {"tricountyindependent.com", "Tri-County Independent (Honesdale, PA)", "biden-tri"},
  {"uticaod.com", "Utica Observer-Dispatch (Utica, NY)", "biden-utica"},
  {"therecordherald.com", "Waynesboro Record Herald (Waynesboro, PA)", "biden-trh"},
  {"ydr.com", "York Daily Record (York, PA)", "biden-ydr"},
 };

  QString text;

 for(auto pr: links)
 {
  QString link  = pr[0];
  QString paper = pr[1];
  QString file = pr[2];

  QString html = R"_(

<p class="Bulleted">&#8226; Neustein, A. and Etlin, M. (2024)  &mdash; OP-ED <a class="Body"
<a href="https://www.%1/story/opinion/2024/07/03/joe-biden-presidential-debate-jill-biden-was-a-voice-of-reason/74279857007/">
<span class="link">Jill Biden is actually a voice of reason following last week&rsquo;s debate debacle</span></a></a>.
<em class="Emphasis">%2</em>, July 3, 2024;
<i>pdf version:</i>
<a href='http://www.amyneustein.com/usan/%3.pdf'>here</a>.
</p>

)_";

  text += html.arg(link).arg(paper).arg(file);




 }

 QString outfile = "/home/nlevisrael/Downloads/biden/usan/o.html";

 KA::TextIO::save_file(outfile, text);

 return 0;

// https://www. story/opinion/2024/07/03/joe-biden-presidential-debate-jill-biden-was-a-voice-of-reason/74279857007/
//                story/opinion/2024/07/03/joe-biden-presidential-debate-jill-biden-was-a-voice-of-reason/74279857007

}


// //   u1 = 1  u2 = 2  QString = 3
 //     u4 = 4  QByteArray = 5
 //     r8 = 6  QVariant = 7
 //     n8 = 8  ? = 9

//chtr-implementation
#include "chtr-asg-visitor/chtr-asg-visitor.h"
#include "chtr-asg-visitor/prerun/chtr-prep-prerun-anticipate.h"

int main(int argc, char *argv[])
{

 ChTR_Document chd(ROOT_FOLDER "/../torq/t1/t1.cr");

 chd.parse();

 chd.report_graph("..txt");

 ChTR_ASG_Visitor visitor(*chd.graph());
 ChTR_Prep_Prerun_Anticipate anticipate(visitor, chd.local_path() + ".cprs");
   
 anticipate.scan(nullptr);
 anticipate.run_core_pairs_generations();




// ChVM_Code_Generator ccg(chrd.graph());

// QString chvm;
// ccg.graph_to_chvm(chvm);
// chrd.save_file("..chvm", chvm);

//? ChVM_Channel_Package_Runner ccr();


 return 0;

 //?chrd.graph_to_chvm();

}



//int main(int argc, char *argv[])
//{
// Chasm_Runtime csr;
// Chasm_Runtime_Bridge crb(&csr);
// Chasm_Procedure_Table cpt(&csr);
// crb.set_proctable(&cpt);

// cpt.register_s0(testqvar, @300762);
// cpt.register_s0(prn, @1001);
// cpt.register_s0(prs, @1003);

// cpt.register_s0(allocate_hypernode, @1000);
// cpt.register_s0(allocate_mempad, @20004);

// cpt.register_s0(demo_opencv, @1003);


// Chasm_VM csm(&crb);
// csm.gen_source_proc_name();
////? csm.load_program(DEMO_CVM_FOLDER "/t1/t1.cvm");
// csm.load_program(DEMO_CVM_FOLDER "/t1/t1.cr.chvm");
// csm.run_current_source_proc_name();
//}


#ifdef HIDE

#include <QPainter>
#include <QPixmap>
#include <QtMath>

#include <QGuiApplication>


QColor interpolate(QColor color1, QColor color2, double fraction)
{

 double r1 = color1.redF();
 double r2 = color2.redF();

 double g1 = color1.greenF();
 double g2 = color2.greenF();

 double b1 = color1.blueF();
 double b2 = color2.blueF();

 double r = ((r2 - r1) * fraction + r1);
 double g = ((g2 - g1) * fraction + g1);
 double b = ((b2 - b1) * fraction + b1);

 return QColor::fromRgbF(r, g, b);
}


int main1(int argc, char *argv[])
{
 QGuiApplication app(argc, argv);

 QString path = ROOT_FOLDER "/../torq/pm.png";

 qDebug() << "path = " << path;

 QPixmap qpm(500, 500);
 QPainter qp(&qpm);

 qpm.fill();

 int r = 220;


 double er = 2;

 const double sq = qSqrt(2) - 1;

 int rotate = 200;

 for(int theta = 0; theta < 3600; ++theta)
 {
  // int thm = theta + rotate % 3600;
  // int thm = theta;

  double thm = theta;
  double thmr = theta + rotate;

  double th10 = thm / 10;
  double thr10 = thmr / 10;

  double radr = qDegreesToRadians(thr10);


  double rad = qDegreesToRadians(th10);

  double x = r * qCos(rad);
  double y = r * qSin(rad);

  double xr = r * qCos(radr);
  double yr = r * qSin(radr);

  QPointF qpf(xr, yr);

  qpf += QPoint{qpm.width()/2, qpm.width()/2};

 // qp.drawEllipse(50 + x - er, 50 + y - er, er * 2, er * 2);

  QColor intermediate = interpolate(Qt::red, Qt::darkRed, thm / 3600);
  qp.setPen(intermediate);


  qp.drawPoint(qpf);


  double max = qMax(qAbs(x), qAbs(y));
  double min = qMin(qAbs(x), qAbs(y));

  double calc = min * sq + max;
  {

   double cx = calc * qCos(radr);
   double cy = calc * qSin(radr);

   //qp.setPen(Qt::darkCyan);
   QColor intermediate = interpolate(Qt::cyan, Qt::darkBlue, thm / 3600);
   qp.setPen(intermediate);


   QPointF cqpf(cx, cy);
   cqpf += QPoint{qpm.width()/2, qpm.width()/2};
   qp.drawPoint(cqpf);
  }

  {
   calc = min * qSqrt(2);

   double cx = calc * qCos(radr);
   double cy = calc * qSin(radr);

//  qp.setPen(Qt::darkMagenta);
   QColor intermediate = interpolate(Qt::magenta, Qt::darkGreen, thm / 3600);
   qp.setPen(intermediate);

   QPointF cqpf(cx, cy);
   cqpf += QPoint{qpm.width()/2, qpm.width()/2};
   qp.drawPoint(cqpf);
  }

  {
   calc = max - calc;

   double cx = calc * qCos(radr);
   double cy = calc * qSin(radr);

   QColor intermediate = interpolate(Qt::yellow, Qt::black, thm / 3600);
   qp.setPen(intermediate);

   QPointF cqpf(cx, cy);
   cqpf += QPoint{qpm.width()/2, qpm.width()/2};
   qp.drawPoint(cqpf);
  }


 }

 qpm.save(path);

}

#endif

