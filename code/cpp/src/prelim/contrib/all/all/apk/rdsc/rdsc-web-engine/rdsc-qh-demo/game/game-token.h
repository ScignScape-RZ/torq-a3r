
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef GAME_TOKEN__H
#define GAME_TOKEN__H

#include "accessors.h"

#include "flags.h"

#include "global-types.h"

#include "enum-macros.h"


#include <QString>

class Game_Position;
class Game_Player;

class Token_Group;

#define Qj(...)

// class c test ...

class Game_Token
{
public:

 // test: -fparse-all-comments
 enum class Token_Kind : u2 {
  N_A

#define enum_macro(x, y) ,x = y

  Qj (enum:def)
  enum_macro(Singleton, 1)
  enum_macro(Paired, 2)
  enum_macro(Queen, 4)
  enum_macro(Jack, 8)
  enum_macro(King, 16)
  enum_macro(Ace, Queen | King)
  enum_macro(South, 32)
  enum_macro(North, 64)

  enum_macro(Clear_Singleton, Paired | Queen | Jack | King | North | South)
  enum_macro(North_South_Mask, North | South)
  enum_macro(Clear_QJK, Paired | North | South)
  enum_macro(Clear_NS, Singleton | Paired | Queen | Jack | King)


  enum_macro(South_Singleton, South | Singleton)
  enum_macro(South_Paired, South | Paired)
  enum_macro(South_Queen, South | Queen)
  enum_macro(South_Jack, South | Jack)
  enum_macro(South_King, South | King)
  enum_macro(South_Ace, South | Ace)

  enum_macro(North_Singleton, North | Singleton)
  enum_macro(North_Paired, North | Paired)
  enum_macro(North_Queen, North | Queen)
  enum_macro(North_Jack, North | Jack)
  enum_macro(North_King, North | King)
  enum_macro(North_Ace, North | Ace)

  Qj (;)

#undef enum_macro
 };

 Qj (enum:ops)
 ENUM_FLAGS_OP_MACROS(Token_Kind, u2)
 Qj (;)



//  Singleton = 1, Paired = 2,  Inner = 4,
//    Buffer = 8, Outer = 16, Inner_Outer = Inner | Outer,

//  South = 32, North = 64,

//  South_Singleton = South | Singleton,
//  South_Paired = South | Paired,
//  South_Inner = South | Inner,
//  South_Buffer = South | Buffer,
//  South_Outer = South | Outer,
//  South_Inner_Outer = South | Inner_Outer,

//  North_Singleton = North | Singleton,
//  North_Paired = North | Paired,
//  North_Inner = North | Inner,
//  North_Buffer = North | Buffer,
//  North_Outer = North | Outer,
//  North_Inner_Outer = North | Inner_Outer,


private:
 Token_Kind kind_;

 //u1 capture_rank_;
//? u1 cluster_size_;

 // //  0 = entry  -1 = on board
  //    otherwise 1-12 = hold file
 s1 capture_status_;

 // //  0 = not checked   -1 = nothing
  //    -1 for move_option_count_ also means
  //    that move_option_capture_count_
  //    has been checked
 s2 move_option_count_;
 s2 move_option_capture_count_;

 Game_Position* current_position_;
 Game_Position* prior_position_;

 QString svg_id_;

 Game_Player* player_;

 Token_Group* current_cluster_;
 QVector<Game_Token*> diagonal_neighbors_;
 QVector<Game_Token*> orthogonal_neighbors_;

 u2 current_placement_order_;

public:

 Game_Token(Game_Player* player, Token_Kind kind = Token_Kind::N_A);

 Qj (accessors)
 ACCESSORS(QString ,svg_id)

 ACCESSORS(s1 ,capture_status)
 ACCESSORS(Game_Player* ,player)

 ACCESSORS(Token_Group* ,current_cluster)


 ACCESSORS(QVector<Game_Token*> ,diagonal_neighbors)
 ACCESSORS(QVector<Game_Token*> ,orthogonal_neighbors)

 ACCESSORS(s1 ,move_option_count)
 ACCESSORS(s1 ,move_option_capture_count)

 ACCESSORS(u2 ,current_placement_order)

 ACCESSORS(Game_Position* ,current_position)
 ACCESSORS(Game_Position* ,prior_position)

 ACCESSORS(Token_Kind ,kind);

 Qj (;)

 QString current_placement_order_label();

 void clear_move_option_count()
 {
  set_move_option_count(0);
 }

 void clear_move_option_capture_count()
 {
  set_move_option_capture_count(0);
 }

 void clear_move_option_counts()
 {
  clear_move_option_count();
  clear_move_option_capture_count();
 }


 u1 current_king_rank();

 u1 current_cluster_size();
 QString current_cluster_status();

 u1 total_density()
 {
  return diagonal_neighbors_.size() + orthogonal_neighbors_.size();
 }

 void clear_neighbors();
 void clear_diagonal_neighbor(Game_Token* other)
 {
  diagonal_neighbors_.removeAll(other);
 }

 void clear_orthogonal_neighbor(Game_Token* other)
 {
  orthogonal_neighbors_.removeAll(other);
 }

 void update_neighbors(const QVector<Game_Token*>& d,
   const QVector<Game_Token*>& o);

 void update_diagonal_neighbor(Game_Token* other)
 {
  if(!diagonal_neighbors_.contains(other))
    diagonal_neighbors_.push_back(other);
 }

 void update_orthogonal_neighbor(Game_Token* other)
 {
  if(!orthogonal_neighbors_.contains(other))
    orthogonal_neighbors_.push_back(other);
 }

 bool south();
 bool north();

 QString token_kind_string()
 {
  //std::string_view ee = magic_enum::enum_name(token_kind_);
  //return QString::fromStdString(ee);

  static QMap<Token_Kind, QString> static_map {

  Qj(enum:str)
  #define enum_macro(x, y)  {Token_Kind::x, #x},

   enum_macro(Singleton, 1)
   enum_macro(Paired, 2)
   enum_macro(Queen, 4)
   enum_macro(Jack, 8)
   enum_macro(King, 16)
   enum_macro(Ace, Queen | King)
   enum_macro(South, 32)
   enum_macro(North, 64)

   enum_macro(South_Singleton, South | Singleton)
   enum_macro(South_Paired, South | Paired)
   enum_macro(South_Queen, South | Queen)
   enum_macro(South_Jack, South | Jack)
   enum_macro(South_King, South | King)
   enum_macro(South_Ace, South | Ace)

   enum_macro(North_Singleton, North | Singleton)
   enum_macro(North_Paired, North | Paired)
   enum_macro(North_Queen, North | Queen)
   enum_macro(North_Jack, North | Jack)
   enum_macro(North_King, North | King)
   enum_macro(North_Ace, North | Ace)

  #undef enum_macro
  Qj(;)


  };

  return static_map.value(kind_, "<error>");
 }


 void hold_current_position();
 bool check_hold_current_position();

 void set_as_north()
 {
  kind_ |= Token_Kind::North;
 }

 void set_as_south()
 {
  kind_ |= Token_Kind::South;
 }


 void set_as_pawn()
 {
  kind_ &= Token_Kind::North_South_Mask;
  kind_ |= Token_Kind::Singleton;
 }

 void set_as_singleton()
 {
  kind_ &= Token_Kind::North_South_Mask;
  kind_ |= Token_Kind::Singleton;
 }

 void set_as_ace()
 {
  kind_ &= Token_Kind::Clear_QJK;
  kind_ |= Token_Kind::Ace;
 }

 void set_as_king()
 {
  kind_ &= Token_Kind::Clear_QJK;
  kind_ |= Token_Kind::King;
 }

 void set_as_queen()
 {
  kind_ &= Token_Kind::Clear_QJK;
  kind_ |= Token_Kind::Queen;
 }

 void set_as_jack()
 {
  kind_ &= Token_Kind::Clear_QJK;
  kind_ |= Token_Kind::Jack;
 }

 void qjk_from_densities(u1 min, u1 max)
 {
  if(total_density() == min)
    set_as_queen();
  else if(total_density() == max)
    set_as_king();
  else
    set_as_jack();
 }





};



#endif // GAME_TOKEN__H