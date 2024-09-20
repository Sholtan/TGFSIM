#ifndef TGFActionInitialization_HH
#define TGFActionInitialization_HH

#include "G4VUserActionInitialization.hh"

#include "TGFPrimaryGenerator.hh"
#include "TGFRunAction.hh"
#include "TGFEventAction.hh"
#include "TGFSteppingAction.hh"




class TGFActionInitialization: public G4VUserActionInitialization
{
public:
	TGFActionInitialization();
	~TGFActionInitialization();

	void SetPrimaryParticleEnergy(G4double);
	void SetAngles(G4double,G4double);
	

	virtual void Build() const;
	virtual void BuildForMaster() const;



private:
	G4double fPrimaryParticleEnergy;
	G4double fInnerAngle;
	G4double fOuterAngle;
};

#endif


