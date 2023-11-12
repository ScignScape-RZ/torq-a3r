
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator/kph-generator.h"

#include "phaon-ir/channel/phr-channel-group.h"

#include "phaon-ir/phr-code-model.h"

#include "phr-direct-eval/phr-direct-eval.h"

#include "phaon-ir/table/phr-symbol-scope.h"

#include "phaon-ir/runtime/phr-command-package.h"

#include "phaon-lib/phr-runner.h"

#include "relae-graph/relae-caon-ptr.h"

#include "phr-env/phr-env.h"
#include "phr-fn-doc/phr-fn-doc.h"



#include <QObject>

#include "kans.h"

#include "textio.h"
USING_KANS(TextIO)


#include "phaon-ir/phaon-ir.h"
#include "phaon-ir/channel/phr-channel-system.h"

#include "phaon-ir/types/phr-type-system.h"

extern void default_phr_startup(PhaonIR& phr);


USING_KANS(Phaon)


int main(int argc, char* argv[])
{
 // //  replace "gen-multi" with "raw-multi"
  //    to test manually-written kph files

 PHR_Channel_System pcs;
 PhaonIR phr(&pcs);
 default_phr_startup(phr);

 phr.type_system()->check_add_type_by_name("ScignStage_Ling_Dialog*", DEFAULT_PTR_BYTE_CODE);
 phr.type_system()->check_add_type_by_name("Lexpair_Dialog*", DEFAULT_PTR_BYTE_CODE);
 phr.type_system()->check_add_type_by_name("QString", DEFAULT_PTR_BYTE_CODE);


 QVector<PHR_Command_Package*> pcps = PHR_Command_Package::parse_multi_from_file(
   phr.channel_system(), phr.type_system(), DEFAULT_KPH_FOLDER "/dataset/gen-multi/t1.kph" );

 QMap<QString, QString> sigs;

 QMap<QString, QVector<PHR_Command_Package*>> qmap;

 PHR_Command_Package::multi_to_map(pcps, qmap);

 QMapIterator<QString, QVector<PHR_Command_Package*>> it(qmap);
 while(it.hasNext())
 {
  it.next();
  for(PHR_Command_Package* pcp: it.value())
  {
   sigs[it.key()] += pcp->moc_signature() + "\n";
  }
 }

 save_file(DEFAULT_KPH_FOLDER "/dataset/gen-multi/t1.kph.sigs",
   sigs["ScignStage_Ling_Dialog*"]);

 save_file(DEFAULT_KPH_FOLDER "/dataset/gen-multi/t1.kph.lexpair.sigs",
   sigs["Lexpair_Dialog*"]);

 return 0;
}
