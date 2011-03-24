with Text_IO;  use Text_IO;
with punchingTerminal; use punchingTerminal;

package body punchingManagement is

   procedure createPunchingTerminal(id : in integer) is
      newPunchingRecord : PunchingRecord;
   begin
      newPunchingRecord.taskAccess := new PunchingTask;
      punchingMap.insert(id, newPunchingRecord);
   end createPunchingTerminal;

   procedure punchTicket(id : in integer) is
   begin
      punchingMap.element(id).taskAccess.all.punch;
   end punchTicket;

end punchingManagement;
