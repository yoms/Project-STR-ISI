with Text_IO;  use Text_IO;

package body composteur is
   task body ComposteurTask is
   begin
      Put_line("start composteur");
      loop
         accept punch
         do
            Put_line("punching ticket");
         end;
      end loop;
   end ComposteurTask;
end composteur;
