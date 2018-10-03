// Contains hard mapped constallation diagrams


#include<complex>
#include<array>

//Defines to compare to in preprocessor macros- to ensure smallest possible mem usage even without optimasation
#define M_BPSK 1
#define M_QPSK 2
#define M_QAM 3
#define M_PSK 4

namespace radio
{
    // Conveniance typedefs
    using cmplx = std::complex<float>;
    // static const std::array<cmplx,8> PSK_8_G = 
    // {{
    // }};

    // so all the preprocessor macrois is suppose to safe space if optimasation is off - not even sure it works 

	#if(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_QPSK )
		constexpr  std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> GetConstalationQPSK()
		{
			static_assert( MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4 , "QPSK needs number of points equal to 4");

			return     {{
								{0.70711,+0.70711},
								{-0.70711,+0.70711},
								{-0.70711,-0.70711},
								{0.70711,-0.70711}
							}} ;


		}
	#endif
    
	#if(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_BPSK)
		constexpr  std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> GetConstalationBPSK()
		{
			static_assert( MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 2 , "BPSK needs number of points equal to 2");
			return  {{
						{1,0},
						{-1,0}
					}};

		}
	#endif

	#if(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_PSK)
		constexpr std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> GetConstalationPSK()
		{
			#if(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 8)
			return{{
						{0.92388,+0.38268},
						{0.38268,+0.92388},
						{-0.38268,+0.92388},
						{-0.92388,+0.38268},
						{-0.92388,-0.38268},
						{-0.38268,-0.92388},
						{0.38268,-0.92388},
						{0.92388,-0.38268} 

			}};
			#elif(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4)
			return
			{{
						{0.70711,+0.70711},
						{-0.70711,+0.70711},
						{-0.70711,-0.70711},
						{0.70711,-0.70711}
			}};
			#endif
			static_assert((MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4) || (MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 8) ,"PSK requires point size of 8 or 4");

		}
	#endif

	#if(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_QAM)
		constexpr  std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> GetConstalationQAM()
		{
			#if(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 8)
			return{{
				{-0.94868,+0.31623},
				{-0.94868,-0.31623},
				{-0.31623,+0.31623},
				{-0.31623,-0.31623},
				{0.31623,+0.31623},
				{0.31623,-0.31623},
				{0.94868,+0.31623},
				{0.94868,-0.31623}
			}};                            
			#elif(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 16)
			return{{
				{-0.70711,+0.70711},
				{-0.70711,+0.2357},
				{-0.70711,-0.2357},
				{-0.70711,-0.70711},
				{-0.2357,+0.70711},
				{-0.2357,+0.2357},
				{-0.2357,-0.2357},
				{-0.2357,-0.70711},
				{0.2357,+0.70711},
				{0.2357,+0.2357},
				{0.2357,-0.2357},
				{0.2357,-0.70711},
				{0.70711,+0.70711},
				{0.70711,+0.2357},
				{0.70711,-0.2357},
				{0.70711,-0.70711}
			}};
			#elif(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 32)
			return{{
				{-0.5145,+0.85749},
				{-0.1715,+0.85749},
				{-0.1715,-0.85749},
				{-0.5145,-0.85749},
				{-0.85749,+0.5145},
				{-0.85749,+0.1715},
				{-0.85749,-0.1715},
				{-0.85749,-0.5145},
				{-0.5145,+0.5145},
				{-0.5145,+0.1715},
				{-0.5145,-0.1715},
				{-0.5145,-0.5145},
				{-0.1715,+0.5145},
				{-0.1715,+0.1715},
				{-0.1715,-0.1715},
				{-0.1715,-0.5145},
				{0.1715,+0.5145},
				{0.1715,+0.1715},
				{0.1715,-0.1715},
				{0.1715,-0.5145},
				{0.5145,+0.5145},
				{0.5145,+0.1715},
				{0.5145,-0.1715},
				{0.5145,-0.5145},
				{0.85749,+0.5145},
				{0.85749,+0.1715},
				{0.85749,-0.1715},
				{0.85749,-0.5145},
				{0.5145,+0.85749},
				{0.1715,+0.85749},
				{0.1715,-0.85749},
				{0.5145,-0.85749}			
			}} ;  
			#elif(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 64) 
			return {{
					{-0.70711,+0.70711},
					{-0.70711,+0.50508},
					{-0.70711,+0.30305},
					{-0.70711,+0.10102},
					{-0.70711,-0.10102},
					{-0.70711,-0.30305},
					{-0.70711,-0.50508},
					{-0.70711,-0.70711},
					{-0.50508,+0.70711},
					{-0.50508,+0.50508},
					{-0.50508,+0.30305},
					{-0.50508,+0.10102},
					{-0.50508,-0.10102},
					{-0.50508,-0.30305},
					{-0.50508,-0.50508},
					{-0.50508,-0.70711},
					{-0.30305,+0.70711},
					{-0.30305,+0.50508},
					{-0.30305,+0.30305},
					{-0.30305,+0.10102},
					{-0.30305,-0.10102},
					{-0.30305,-0.30305},
					{-0.30305,-0.50508},
					{-0.30305,-0.70711},
					{-0.10102,+0.70711},
					{-0.10102,+0.50508},
					{-0.10102,+0.30305},
					{-0.10102,+0.10102},
					{-0.10102,-0.10102},
					{-0.10102,-0.30305},
					{-0.10102,-0.50508},
					{-0.10102,-0.70711},
					{0.10102,+0.70711},
					{0.10102,+0.50508},
					{0.10102,+0.30305},
					{0.10102,+0.10102},
					{0.10102,-0.10102},
					{0.10102,-0.30305},
					{0.10102,-0.50508},
					{0.10102,-0.70711},
					{0.30305,+0.70711},
					{0.30305,+0.50508},
					{0.30305,+0.30305},
					{0.30305,+0.10102},
					{0.30305,-0.10102},
					{0.30305,-0.30305},
					{0.30305,-0.50508},
					{0.30305,-0.70711},
					{0.50508,+0.70711},
					{0.50508,+0.50508},
					{0.50508,+0.30305},
					{0.50508,+0.10102},
					{0.50508,-0.10102},
					{0.50508,-0.30305},
					{0.50508,-0.50508},
					{0.50508,-0.70711},
					{0.70711,+0.70711},
					{0.70711,+0.50508},
					{0.70711,+0.30305},
					{0.70711,+0.10102},
					{0.70711,-0.10102},
					{0.70711,-0.30305},
					{0.70711,-0.50508},
					{0.70711,-0.70711}
				}}; 
			#elif(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 128)
			return  {{
					{-0.53688,+0.69027},
					{-0.53688,+0.84366},
					{-0.076696,+0.84366},
					{-0.076696,+0.69027},
					{-0.076696,-0.69027},
					{-0.076696,-0.84366},
					{-0.53688,-0.84366},
					{-0.53688,-0.69027},
					{-0.38348,+0.69027},
					{-0.38348,+0.84366},
					{-0.23009,+0.84366},
					{-0.23009,+0.69027},
					{-0.23009,-0.69027},
					{-0.23009,-0.84366},
					{-0.38348,-0.84366},
					{-0.38348,-0.69027},
					{-0.84366,+0.53688},
					{-0.84366,+0.38348},
					{-0.84366,+0.23009},
					{-0.84366,+0.076696},
					{-0.84366,-0.076696},
					{-0.84366,-0.23009},
					{-0.84366,-0.38348},
					{-0.84366,-0.53688},
					{-0.69027,+0.53688},
					{-0.69027,+0.38348},
					{-0.69027,+0.23009},
					{-0.69027,+0.076696},
					{-0.69027,-0.076696},
					{-0.69027,-0.23009},
					{-0.69027,-0.38348},
					{-0.69027,-0.53688},
					{-0.53688,+0.53688},
					{-0.53688,+0.38348},
					{-0.53688,+0.23009},
					{-0.53688,+0.076696},
					{-0.53688,-0.076696},
					{-0.53688,-0.23009},
					{-0.53688,-0.38348},
					{-0.53688,-0.53688},
					{-0.38348,+0.53688},
					{-0.38348,+0.38348},
					{-0.38348,+0.23009},
					{-0.38348,+0.076696},
					{-0.38348,-0.076696},
					{-0.38348,-0.23009},
					{-0.38348,-0.38348},
					{-0.38348,-0.53688},
					{-0.23009,+0.53688},
					{-0.23009,+0.38348},
					{-0.23009,+0.23009},
					{-0.23009,+0.076696},
					{-0.23009,-0.076696},
					{-0.23009,-0.23009},
					{-0.23009,-0.38348},
					{-0.23009,-0.53688},
					{-0.076696,+0.53688},
					{-0.076696,+0.38348},
					{-0.076696,+0.23009},
					{-0.076696,+0.076696},
					{-0.076696,-0.076696},
					{-0.076696,-0.23009},
					{-0.076696,-0.38348},
					{-0.076696,-0.53688},
					{0.076696,+0.53688},
					{0.076696,+0.38348},
					{0.076696,+0.23009},
					{0.076696,+0.076696},
					{0.076696,-0.076696},
					{0.076696,-0.23009},
					{0.076696,-0.38348},
					{0.076696,-0.53688},
					{0.23009,+0.53688},
					{0.23009,+0.38348},
					{0.23009,+0.23009},
					{0.23009,+0.076696},
					{0.23009,-0.076696},
					{0.23009,-0.23009},
					{0.23009,-0.38348},
					{0.23009,-0.53688},
					{0.38348,+0.53688},
					{0.38348,+0.38348},
					{0.38348,+0.23009},
					{0.38348,+0.076696},
					{0.38348,-0.076696},
					{0.38348,-0.23009},
					{0.38348,-0.38348},
					{0.38348,-0.53688},
					{0.53688,+0.53688},
					{0.53688,+0.38348},
					{0.53688,+0.23009},
					{0.53688,+0.076696},
					{0.53688,-0.076696},
					{0.53688,-0.23009},
					{0.53688,-0.38348},
					{0.53688,-0.53688},
					{0.69027,+0.53688},
					{0.69027,+0.38348},
					{0.69027,+0.23009},
					{0.69027,+0.076696},
					{0.69027,-0.076696},
					{0.69027,-0.23009},
					{0.69027,-0.38348},
					{0.69027,-0.53688},
					{0.84366,+0.53688},
					{0.84366,+0.38348},
					{0.84366,+0.23009},
					{0.84366,+0.076696},
					{0.84366,-0.076696},
					{0.84366,-0.23009},
					{0.84366,-0.38348},
					{0.84366,-0.53688},
					{0.38348,+0.69027},
					{0.38348,+0.84366},
					{0.23009,+0.84366},
					{0.23009,+0.69027},
					{0.23009,-0.69027},
					{0.23009,-0.84366},
					{0.38348,-0.84366},
					{0.38348,-0.69027},
					{0.53688,+0.69027},
					{0.53688,+0.84366},
					{0.076696,+0.84366},
					{0.076696,+0.69027},
					{0.076696,-0.69027},
					{0.076696,-0.84366},
					{0.53688,-0.84366},
					{0.53688,-0.69027}
				}}  ;
			#endif  


		}
	#endif




    constexpr  std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> GetConstalation()
    {
        #if(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_QPSK )
            return GetConstalationQPSK();
        #elif(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_BPSK)
            return GetConstalationBPSK();

        #elif(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_QAM)
            return GetConstalationQAM();

		#elif(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_PSK)
            return GetConstalationPSK();
	

        // #elif(MBED_CONF_CONSTALATIONDIAGRAMS_MODULATION == M_PSK)


        #endif 
    } 













     class ConstalationDiagram
     {
     public:
         ConstalationDiagram();
		 //might want to dissable copy constructor
         ConstalationDiagram(ConstalationDiagram &&) = default;
         ConstalationDiagram(const ConstalationDiagram &) = default; 
         ConstalationDiagram &operator=(ConstalationDiagram &&) = default;
         ConstalationDiagram &operator=(const ConstalationDiagram &) = default;
         ~ConstalationDiagram();



         

     
     private:

	 	const std::array<cmplx,MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS> m_aConstalationMapping = GetConstalation();
         
     };
     
     ConstalationDiagram::ConstalationDiagram()
     {
     }
     
     ConstalationDiagram::~ConstalationDiagram()
     {
     }


}

 static std::complex<double> first (2.0,2.0);

