with Text_IO;

package body punchingTerminal is
  use Text_IO;
   task body PunchingTask is
   begin
      Put_line("start punching task");
      loop
         accept punch
         do
         	delay 1.0;
            Put_line("punching ticket");
         end;
      end loop;
   end PunchingTask;
end punchingTerminal;
