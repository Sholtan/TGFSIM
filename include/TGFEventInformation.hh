#ifndef TGFEventInformation_HH
#define TGFEventInformation_HH

#include "G4VUserEventInformation.hh"


#include "G4ThreeVector.hh"


class TGFEventInformation: public G4VUserEventInformation
{
public:
	TGFEventInformation();
	~TGFEventInformation();

	virtual void Print() const {G4cout << "pure virtual Print called" << G4endl;}

	void SetPrimaryMomentumVector(G4ThreeVector);
	G4ThreeVector GetPrimaryMomentumVector();

private:
	G4ThreeVector fPrimaryMomentumVector;
};

#endif
