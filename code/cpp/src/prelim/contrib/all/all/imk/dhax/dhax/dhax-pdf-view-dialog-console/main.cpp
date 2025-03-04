
#include "dhax-pdf-view-dialog/paraviews/dhax-pdf-view-dialog.h"
#include "dhax-pdf-view-dialog/pleneviews/view-pdf-frame.h"
#include "dhax-pdf-view-dialog/subwindows/pdf-document-widget.h"

#include <QApplication>

//USING_QSNS(Cy_Mesh)

#include "m2m.h"

#include "index-entry-review-dialog.h"

int main(int argc, char *argv[])
{
 QString ifile = "/home/nlevisrael/Downloads/m2m/w_pdf/dindex.txt";
// QString ofile = "/home/nlevisrael/Downloads/m2m/w_pdf/tindex.txt";

 QString nfile = "/home/nlevisrael/Downloads/m2m/w_pdf/notes.txt";
 QString n1file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes1.txt";

// QString otext;
// QTextStream oqts(&otext);

// write_index_entries(index_entries, oqts);
// KA::TextIO::save_file(ofile, otext);

// return 0;


 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile);

 ierd->show();

// DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr,
//   "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
//   nfile,
//   32);

// pvd->show();


// DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(nullptr,
//   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
//   n1file,
//   13);

// pvd1->show();


 qapp.exec();
 return 0;
}

//ROOT_FOLDER "/../docs/ch6.pdf");
