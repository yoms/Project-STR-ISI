package punchingTerminal is

   task type PunchingTask is
      entry punch;
   end PunchingTask;

   type PunchingTaskAccess is access PunchingTask;

   type PunchingRecord is
      record
         taskAccess:PunchingTaskAccess;
      end record;

end punchingTerminal;
