 %{
 BPSKMod = comm.BPSKModulator;
 constellation(BPSKMod);
 print('BPSK','-djpeg');
 BPSKModConst =  constellation(BPSKMod);
 csvwrite("BPSK.csv",BPSKModConst);
 
 grayQpsk = comm.QPSKModulator;
 constellation(grayQpsk);
 print('QPSK-G','-djpeg');
 grayQpskConst = constellation(grayQpsk);
 csvwrite("QPSK-G.csv",grayQpskConst);
 
 
 binaryQpsk = comm.QPSKModulator ;
 binaryQpsk.SymbolMapping = 'Binary';
 constellation(binaryQpsk);
 print('QPSK-B','-djpeg');
 binaryQpskConst = constellation(binaryQpsk);
 csvwrite("QPSK-B.csv",binaryQpskConst);
%}
 
%{

 qamBinary8 = comm.RectangularQAMModulator('ModulationOrder',8, 'SymbolMapping','binary');
 qamBinary8.NormalizationMethod = "Peak power";
 constellation(qamBinary8);
 print('QAM-8-B-PeakPower','-djpeg');
 qamBinary8Const = constellation(qamBinary8);
 csvwrite("QAM-8-B-PeakPower.csv",qamBinary8Const);
 
  qamBinary8.NormalizationMethod = "Average power";
 constellation(qamBinary8);
 print('QAM-8-B-AvgPower','-djpeg');
 qamBinary8Const = constellation(qamBinary8);
 csvwrite("QAM-8-B-AvgPower.csv",qamBinary8Const);

%}

%{
 qamGray8 = comm.RectangularQAMModulator('ModulationOrder',8, 'SymbolMapping','Gray');
 qamGray8.NormalizationMethod = "Peak power";
 constellation(qamGray8);
 print('QAM-8-G-PeakPower','-djpeg');
 qamGray8Const = constellation(qamGray8);
 csvwrite("QAM-8-G-PeakPower.csv",qamGray8Const);
 
  qamGray8.NormalizationMethod = "Average power";
 constellation(qamGray8);
 print('QAM-8-G-AvgPower','-djpeg');
 qamGray8Const = constellation(qamGray8);
 csvwrite("QAM-8-G-AvgPower.csv",qamGray8Const);
%}

%{
 qamGray16 = comm.RectangularQAMModulator('ModulationOrder',16, 'SymbolMapping','Gray');
 qamGray16.NormalizationMethod = "Peak power";
 constellation(qamGray16);
 print('QAM-16-G-PeakPower','-djpeg');
 qamBinary16Const = constellation(qamGray16);
 csvwrite("QAM-16-G-PeakPower.csv",qamBinary16Const);
 
  qamGray16.NormalizationMethod = "Average power";
 constellation(qamGray16);
 print('QAM-16-G-AvgPower','-djpeg');
 qamBinary16Const = constellation(qamGray16);
 csvwrite("QAM-16-G-AvgPower.csv",qamBinary16Const);
%}

%{
 qamBinary16 = comm.RectangularQAMModulator('ModulationOrder',16, 'SymbolMapping','Binary');
 qamBinary16.NormalizationMethod = "Peak power";
 constellation(qamBinary16);
 print('QAM-16-B-PeakPower','-djpeg');
 qamBinary16Const = constellation(qamBinary16);
 csvwrite("QAM-16-B-PeakPower.csv",qamBinary16Const);
 
 qamBinary16.NormalizationMethod = "Average power";
 constellation(qamBinary16);
 print('QAM-16-B-AvgPower','-djpeg');
 qamBinary16Const = constellation(qamBinary16);
 csvwrite("QAM-16-B-AvgPower.csv",qamBinary16Const);
%}

%{
 qamBinary32 = comm.RectangularQAMModulator('ModulationOrder',32, 'SymbolMapping','Binary');
 qamBinary32.NormalizationMethod = "Peak power";
 constellation(qamBinary32);
 print('QAM-32-B-PeakPower','-djpeg');
 qamBinary32Const = constellation(qamBinary32);
 csvwrite("QAM-32-B-PeakPower.csv",qamBinary32Const);
 
 qamBinary32.NormalizationMethod = "Average power";
 constellation(qamBinary32);
 print('QAM-32-B-AvgPower','-djpeg');
 qamBinary32Const = constellation(qamBinary32);
 csvwrite("QAM-32-B-AvgPower.csv",qamBinary32Const);
%}
%{
 qamGray32 = comm.RectangularQAMModulator('ModulationOrder',32, 'SymbolMapping','Gray');
 qamGray32.NormalizationMethod = "Peak power";
 constellation(qamGray32);
 print('QAM-32-G-PeakPower','-djpeg');
 qamGrayConst = constellation(qamGray32);
 csvwrite("QAM-32-G-PeakPower.csv",qamGrayConst);
 
 qamGray32.NormalizationMethod = "Average power";
 constellation(qamGray32);
 print('QAM-32-G-AvgPower','-djpeg');
 qamGrayConst = constellation(qamGray32);
 csvwrite("QAM-32-G-AvgPower.csv",qamGrayConst);
%}
%{
 qamGray64 = comm.RectangularQAMModulator('ModulationOrder',64, 'SymbolMapping','Gray');
 qamGray64.NormalizationMethod = "Peak power";
 constellation(qamGray64);
 print('QAM-64-G-PeakPower','-djpeg');
 qamGrayConst = constellation(qamGray64);
 csvwrite("QAM-64-G-PeakPower.csv",qamGrayConst);
 
 qamGray64.NormalizationMethod = "Average power";
 constellation(qamGray64);
 print('QAM-64-G-AvgPower','-djpeg');
 qamGrayConst = constellation(qamGray64);
 csvwrite("QAM-64-G-AvgPower.csv",qamGrayConst);
%}
%{
 qamBinary64 = comm.RectangularQAMModulator('ModulationOrder',64, 'SymbolMapping','Binary');
 qamBinary64.NormalizationMethod = "Peak power";
 constellation(qamBinary64);
 print('QAM-64-B-PeakPower','-djpeg');
 qamBinaruConst = constellation(qamBinary64);
 csvwrite("QAM-64-B-PeakPower.csv",qamBinaruConst);
 
 qamBinary64.NormalizationMethod = "Average power";
 constellation(qamBinary64);
 print('QAM-64-B-AvgPower','-djpeg');
 qamBinaruConst = constellation(qamBinary64);
 csvwrite("QAM-64-B-AvgPower.csv",qamBinaruConst);
%}


%{
 qamBinary128 = comm.RectangularQAMModulator('ModulationOrder',128, 'SymbolMapping','Binary');
 qamBinary128.NormalizationMethod = "Peak power";
 constellation(qamBinary128);
 print('QAM-128-B-PeakPower','-djpeg');
 qamBinaruConst = constellation(qamBinary128);
 csvwrite("QAM-128-B-PeakPower.csv",qamBinaruConst);
 
 qamBinary128.NormalizationMethod = "Average power";
 constellation(qamBinary128);
 print('QAM-128-B-AvgPower','-djpeg');
 qamBinaruConst = constellation(qamBinary128);
 csvwrite("QAM-128-B-AvgPower.csv",qamBinaruConst);
%}

%{
 qamGra128 = comm.RectangularQAMModulator('ModulationOrder',128, 'SymbolMapping','Gray');
 qamGra128.NormalizationMethod = "Peak power";
 constellation(qamGra128);
 print('QAM-128-G-PeakPower','-djpeg');
 qamGrConst = constellation(qamGra128);
 csvwrite("QAM-128-G-PeakPower.csv",qamGrConst);
 
 qamGra128.NormalizationMethod = "Average power";
 constellation(qamGra128);
 print('QAM-128-G-AvgPower','-djpeg');
 qamGrConst = constellation(qamGra128);
 csvwrite("QAM-128-G-AvgPower.csv",qamGrConst);
%}

PSKMOD = comm.PSKModulator;
PSKMOD.ModulationOrder = 8;
constellation(PSKMOD);
print('PSK-8-G','-djpeg');
PSKMODCONST = constellation(PSKMOD);
csvwrite("PSK-8-G.csv",PSKMODCONST);



PSKMOD.SymbolMapping = "Binary"; 
constellation(PSKMOD);
print('PSK-8-B','-djpeg');
PSKMODCONST = constellation(PSKMOD);
csvwrite("PSK-8-B.csv",PSKMODCONST);


constellation(PSKMOD);



