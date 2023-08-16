
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_DRIVER__H
#define GAME_DRIVER__H

#include "accessors.h"

#include "flags.h"

#include "game-board.h"

class Game_Token;
class Game_Player;

class Token_Group;
class Game_Variant;

class Message_Display_Window;

class Game_Driver
{
 Game_Board board_;

 Game_Variant* current_variant_;

 QMap<QString, Game_Token*> tokens_by_svg_id_;
 QMap<u2, Game_Player*> players_by_player_order_;

 QMap<QString, Game_Token*> tokens_by_text_indicator_;

 struct Move_Indicator { QString id; Game_Position* current_position; };
 QVector<Move_Indicator*> move_indicators_;
 QVector<Move_Indicator*> capture_move_indicators_;
 u2 move_indicators_count_;
 u2 move_indicators_capture_count_;

 void js_show_move_indicators(QH_Web_View_Dialog& dlg);

 struct Chess_Icon { QString file_path; QString svg_id; };
 QMap<QString, Chess_Icon*> north_chess_icons_;
 QMap<QString, Chess_Icon*> south_chess_icons_;

 QMap<Game_Token*, Chess_Icon*> tokens_on_board_;

 Game_Token* current_selected_token_;

 Game_Player* current_player_;
 Game_Player* south_player_;
 Game_Player* north_player_;

 enum class Game_States { N_A, Neutral, North_to_Move, North_to_Move_2_of_2,
    North_to_Place, South_to_Move, South_to_Move_2_of_2, South_to_Place };

 enum class Indicator_Status { N_A, Text, Chess_Icons };
 Indicator_Status current_indicator_status_;

 Game_States current_state_;

 Message_Display_Window* message_display_window_;

 void _place(Game_Token* token, Game_Position* gp);
 void _place(Game_Token* token, Token_Group* cluster);
 void _place_confirmed(Game_Token* token, Token_Group* cluster);

 struct _surrounding {
  QVector<Token_Group*> clusters;
 // QVector<Game_Token*> cluster_tokens;
  QVector<Game_Token*> singletons;
  QVector<Game_Token*> diagonal;
  QVector<Game_Token*> orthogonal;
 };

 u1 check_cluster(Game_Token* token, _surrounding& s);

 void display_message(QString msg, QH_Web_View_Dialog* dlg = nullptr);

 void get_token_info(Game_Token* token);

 Game_Token* get_token_for_placement();

 void js_highlight_token(Game_Token* token, QH_Web_View_Dialog& dlg);
 void js_unhighlight_token(Game_Token* token, QH_Web_View_Dialog& dlg);

 void js_hide_move_indicators(QH_Web_View_Dialog& dlg);
 void check_reset_move_indicators(QH_Web_View_Dialog& dlg);

 QString current_player_string();

 void show_chess_icon(const QH_Web_View_Dialog& dlg,
   Game_Token* token, Game_Driver::Chess_Icon* icon);

 void show_chess_icon(const QH_Web_View_Dialog& dlg, Game_Token* token);

 void hide_chess_icons(const QH_Web_View_Dialog& dlg);
 void clear_move_option_data();

public:

 Game_Driver();

 ACCESSORS__RGET(Game_Board ,board)

 ACCESSORS(Message_Display_Window* ,message_display_window)

 void show_token_at_position(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);

 void handle_move_indicator_clicked(QH_Web_View_Dialog& dlg, QString id);

 void show_chess_icons(const QH_Web_View_Dialog& dlg);
 void register_north_chess_icon(QString file_path, QString svg_id);
 void register_south_chess_icon(QString file_path, QString svg_id);

 void register_move_indicator(QString id);
 void register_capture_move_indicator(QString id);

 Game_Position* get_game_position_via_offset(Game_Position* starting, QPair<s2, s2> offsets);

 void start_game(QH_Web_View_Dialog& dlg);
 void check_token_chess_icon(Game_Token* token);


 void handle_text_indicator_clicked(QH_Web_View_Dialog& dlg, QString token_id);
 void handle_token_clicked(QH_Web_View_Dialog& dlg, QString token_id);
 void handle_token_clicked(QH_Web_View_Dialog& dlg, Game_Token* token);

 void handle_position_clicked(QH_Web_View_Dialog& dlg, QString position_id);
 void handle_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, QString pos_id);

 Game_Token* handle_non_slot_token_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);

 void switch_players(QH_Web_View_Dialog& dlg);

 void handle_position_context_menu(QH_Web_View_Dialog& dlg,  QString position_id, const QPoint& global_position);
 void handle_token_context_menu(QH_Web_View_Dialog& dlg, QString token_id, const QPoint& global_position);

 void register_token(QString key, Game_Token* token);
 Game_Token* register_new_token(u1 player_order, QString key);

 Game_Token* confirm_token_placement(QH_Web_View_Dialog& dlg);
 void check_prepare_token_placement(Game_Token* token, QH_Web_View_Dialog& dlg);
 void switch_current_player();

 void run_js_code(const QH_Web_View_Dialog& dlg, QString js);
 void run_js_for_current_player(const QH_Web_View_Dialog& dlg, QString js);
 void highlight_current_player_sidebar(const QH_Web_View_Dialog& dlg);

 void show_text_indicators(const QH_Web_View_Dialog& dlg);
 void hide_text_indicators(const QH_Web_View_Dialog& dlg);

 Token_Group* merge_token_groups(const QVector<Token_Group*>& clusters);
 Token_Group* merge_token_groups(const QVector<Token_Group*>& clusters, const QVector<Game_Token*>& tokens);
 void merge_tokens_into_group(Token_Group* cluster, const QVector<Game_Token*>& tokens);
 Token_Group* merge_tokens_into_new_group(const QVector<Game_Token*>& tokens);

 void prepare_move_option_indicators(Game_Token* token, QH_Web_View_Dialog& dlg);
 void finalize_token_move(Game_Token* token, Move_Indicator* mi, QH_Web_View_Dialog& dlg);
 void finalize_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);
 void finalize_token_move(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);
 void handle_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);
 void update_token_move_or_placement(QH_Web_View_Dialog& dlg, Game_Token* token, Game_Position* gp);


};



#endif // GAME_DRIVER__H