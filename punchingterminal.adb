with Text_IO;  use Text_IO;

package body punchingTerminal is
   task body PunchingTask is
   begin
      Put_line("start punching task");
      loop
         accept punch
         do
            Put_line("punching ticket");
         end;
      end loop;
   end PunchingTask;
end punchingTerminal;
