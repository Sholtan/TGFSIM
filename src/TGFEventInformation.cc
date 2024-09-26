#include "TGFEventInformation.hh"

TGFEventInformation::TGFEventInformation()
{
	//G4cout << G4endl << G4endl << "TGFEventInformation object was created" << G4endl << G4endl;
}

TGFEventInformation::~TGFEventInformation()
{}




void TGFEventInformation::SetPrimaryMomentumVector(G4ThreeVector PrimaryMomentumVector)
{
	fPrimaryMomentumVector = PrimaryMomentumVector;
}

G4ThreeVector TGFEventInformation::GetPrimaryMomentumVector()
{
	return fPrimaryMomentumVector;
}
