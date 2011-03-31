package punchingManagement is

   task type PunchingTask is
      entry punch;
   end PunchingTask;

   punchingTab : array(1..10) of PunchingTask;

   procedure adaPunchTicket(id : integer);

end punchingManagement;
