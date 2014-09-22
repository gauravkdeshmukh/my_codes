with TEXT_IO; use TEXT_iO;

procedure sieve is

	package INT_IO is new INTEGER_IO(INTEGER); use iNT_iO;

	type NumRec is record
		print  : BOOLEAN;
		number : INTEGER;
	end Record;

	no :INTEGER := 1;
	task Generator is
		entry StartGenerator;
	end Generator;

	task printer is
		entry StartPrinter;
		entry GetNum(Item : in numRec);
	end printer;

	task type Sieve is
		entry MyNumber(num , last : in INTEGER);
		entry catchNum(item : in numRec);
	end Sieve;

	type SievePtr is access Sieve;
	type Vector is array(2..1000) of sievePtr;

	p: INTEGER;
	S: VECTOR;

	task body Generator is
		Value : INTEGER;
		Item  : NumRec;
	begin
		accept StartGenerator do
			null;
		end StartGenerator;
		value :=1;
		loop
			value := value + 1;
			item.print := True;
			Item.number := value;
			S(no+1).catchNum(Item); -- Rendevous point with Sieve
		end loop;
	end generator;

	task body printer is
		LocalRec : NumRec;
	begin
		accept startPrinter do
 	    	null;
		end StartPrinter;
		loop
			accept getNum(item : in numRec) do
				localRec := item;
			end getNum;
			if (localRec.Print) then
				PUT("Number=>");
				PUT(LocalRec.number,6);
				NEW_lINE;
			end if;
		end loop;
	end printer;

		task body Sieve  is
		m : INTEGER;
		n : INTEGER;
		LocalRec : NumRec;
		begin
			accept MyNumber(Num : in INTEGER; LAST : in INTEGER) do
			m := Num;
			n := Last;
			end MyNumber;
			Loop
				exit when m > n;
				accept catchNum(Item : in NumRec) do
				localRec := Item;
				end CatchNum;
				if(m = localRec.number) and (localrec.number mod m) = 0 then
					localRec.Print := FALSE;
				end if;
				if(m < n) then
					s(No+1).CatchNum(LocalREc);
				else
					Printer.GetNum(localRec);
				end if;
			end loop;
		end sieve;

begin

	PUT("Number of sieve tasks to generate?");
	get(P);

	for i in 2..p+1 loop
		S(i) := new sieve;
	end loop;

	Generator.StartGenerator;
	Printer.startPrinter;

	for i in 2..p+1 loop
		s(i).myNumber(i,p+1);
	end loop;

end sieve;
