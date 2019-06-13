(* Выводит в скрипт команды вставки из файлов символов скважин в локальных координатах
   Символы помещаются в слой "WELLS" *)
function TfrmWellPlace.PlotWellsSymbol : integer;
var
  f : TextFile;
  x, y : Double;
  x1, y1,
  x2, y2: integer;
  s : string;
begin
  AssignFile( f, feFileName.Text );
  try
//Create file
    Rewrite( f );
//Create new layer: name=WELLS, colour, line style and othe is default
    AS_LayerCreate(f, 'WELLS');
    with _db.data.qryWellPlace do begin
      if not Active then
        Open();
      First();
      while not Eof do begin
//get well coordinates
        x := FieldByName('x').asFloat + edXShift.Value;
        y := FieldByName('y').asFloat + edYShift.Value;
        if ckStateSymbol.Checked then
          s := '_w_DEV' //ignore well state symbol, all wells plot simple circle
        else
          s := FieldByName('DWG_file').asString;
//Plot block from file at specified position
        AS_InsertBlock(f, Lib_Path + s + '.dwg', x, y, Round(edScale.Value), Round(edScale.Value), 0);
        Next();
      end;
      Close();
    end;
  finally
    CloseFile(f);
  end;
end;
