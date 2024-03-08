
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-asg-visitor.h"

#include "rzns.h"

USING_RZNS(GBuild)


RZ_ASG_Visitor_Run_State::RZ_ASG_Visitor_Run_State()
 : Flags(0), read_table_state_(RZ_Read_Table_State::Inactive),
    post_advance_state_(RZ_Read_Table_Post_Advance_State::N_A),
    advance_token_state_(RZ_Read_Table_Advance_Token_State::Token_Loaded)
{

}


