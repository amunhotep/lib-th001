{$DEFINE PEAKTOP:COM/GOOGLE/MAPS/API.INC}
{$IFNDEF PEAKTOP:COM/GOOGLE/MAPS/CONST.INC}{$I ./CONST.INC}{$ENDIF}
type //============== PEAKTOP:COM/GOOGLE/MAPS/API.INC ========================== 
  TGoogleMapsZoom       = 1..16;
  TGoogleMapsSize       = 1..640;
  TGoogleMapsTypeEnum   = (gmtMap, gmtSatellite, gmtHybrid);
  TGoogleMapsFormatEnum = (gmfPNG, gmfJPEG, gmfGIF);
  
