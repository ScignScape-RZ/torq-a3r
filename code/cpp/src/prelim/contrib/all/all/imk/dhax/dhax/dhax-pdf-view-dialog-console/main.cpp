
#include "dhax-pdf-view-dialog/paraviews/dhax-pdf-view-dialog.h"
#include "dhax-pdf-view-dialog/pleneviews/view-pdf-frame.h"
#include "dhax-pdf-view-dialog/subwindows/pdf-document-widget.h"

#include <QApplication>

//USING_QSNS(Cy_Mesh)

#include "indexing/m2m.h"

#include "indexing/index-entry-review-dialog.h"

int main1(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QString n1file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes1.txt";

 DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(nullptr,nullptr,
   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
   n1file, 1);

 pvd1->setWindowTitle("Earlier Document");
 pvd1->show();

 qapp.exec();
 return 0;
}

int main(int argc, char *argv[])
{
 QString ifile = "/home/nlevisrael/Downloads/m2m/w_pdf/dindex.txt";
// QString ofile = "/home/nlevisrael/Downloads/m2m/w_pdf/tindex.txt";

 QString n1file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes1.txt";
 QString n2file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes2.txt";

// QString otext;
// QTextStream oqts(&otext);

// write_index_entries(index_entries, oqts);
// KA::TextIO::save_file(ofile, otext);

// return 0;


 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile);


 DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(nullptr, ierd,
   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
   n1file,
   13);

 pvd1->setWindowTitle("Earlier Document");
 pvd1->show();

 DHAX_PDF_View_Dialog* pvd2 = new DHAX_PDF_View_Dialog(nullptr, ierd,
   "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
   n2file,
   32);

 pvd2->setWindowTitle("Later Document");
 pvd2->show();

 ierd->set_earlier_pdf_dialog(pvd1);
 ierd->set_later_pdf_dialog(pvd2);

 ierd->show();

 qapp.exec();
 return 0;
}

//ROOT_FOLDER "/../docs/ch6.pdf");
