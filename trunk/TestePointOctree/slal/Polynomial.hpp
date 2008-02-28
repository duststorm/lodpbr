#ifndef POLYNOMIAL_HPP_
#define POLYNOMIAL_HPP_

namespace CGL
{


	template <class Real> class CubicEquation
	{
	
	private:
		//Coeficientes
		Real mA;
		Real mB;
		Real mC;
		Real mD;
		
		Real mH;
		Real mG;
		Real mF;
		
		bool m3RootAreReal;
		bool m3RootAreRealAndEqual;
		bool mOnly1RootIsReal;
		
		bool solver()
		{
			;
		}
		
	public:
					
		CubicEquation(const Real& a, 
					  const Real& b, 
					  const Real& c,
					  const Real& d) : 	mA(a),mB(b),mC(c),mD(d),
					  					m3RootAreReal(false),
					  					m3RootAreRealAndEqual(false),
					  					mOnly1RootIsReal(false)
		{
			
		};
		
		template <class C>
		CubicEquation(const C* pArray)
		{
			assert(p);
			
	    	mA = static_cast< Real > ( pArray[0] );
	    	mB = static_cast< Real > ( pArray[1] );
	    	mC = static_cast< Real > ( pArray[2] );
	    	mD = static_cast< Real > ( pArray[3] );
	    	
		}
		
		static const bool is3RootAreReal () const 
		{
			return m3RootAreReal;
		};
		static const bool is3RootAreRealAndEqual() const
		{
			return m3RootAreRealAndEqual;
		}
		static const bool isOnly1RootIsReal() const
		{
			return mOnly1RootIsReal;
		};
		
						
		virtual ~CubicEquation(){};
	};

}/* CGL :: NAMESPACE */

#endif /*POLYNOMIAL_HPP_*/
