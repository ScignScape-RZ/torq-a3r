#ifndef  color_generic_make_green
#define color_generic_make_green

// ::color::make::green( c )

// TODO #include "model.hpp"
#include "../constant/green.hpp"


 namespace color
  {
   namespace constant
    {

     template< typename category_name >
      struct make< ::color::constant::green_t, category_name >
       {
        typedef category_name                         category_type;
        typedef ::color::model<category_type>            model_type;
        typedef ::color::rgb<double>                       rgb_type;
        typedef ::color::constant::green_t            constant_type;

        typedef typename ::color::trait::container<category_type>::output_type       container_output_type;

        inline static void process( container_output_type & container )
         {
          static model_type  s_model{ rgb_type{ 0, 0.5, 0 } };
          container = s_model.container();
         }
       };

     template< typename category_name >
      struct make< ::color::constant::x11::green_t, category_name >
       {
        typedef category_name                        category_type;
        typedef ::color::model<category_type>           model_type;
        typedef ::color::rgb<double>                      rgb_type;
        typedef ::color::constant::x11::green_t     constant_type;

        typedef typename ::color::trait::container<category_type>::output_type       container_output_type;

        inline static void process( container_output_type & container )
         {
          static model_type  s_model{ rgb_type{ 0, 1, 0 } };

          container = s_model.container();
         }
       };

    }
  }

#endif
