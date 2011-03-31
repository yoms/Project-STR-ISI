with Text_IO; use Text_IO;

package body punchingManagement is

	task body PunchingTask is
   begin
      loop
         accept punch
         do
            delay 1.0;
         end;
      end loop;
   end PunchingTask;

   procedure adaPunchTicket(id : integer) is
   begin
      punchingTab(id).punch;
   end adaPunchTicket;

end punchingManagement;
