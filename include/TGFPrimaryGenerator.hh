#ifndef TGFPrimaryGenerator_HH
#define TGFPrimaryGenerator_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

#include "Randomize.hh"

class TGFPrimaryGenerator: public G4VUserPrimaryGeneratorAction
{
public:
	TGFPrimaryGenerator();
	~TGFPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);

	void SetPrimaryEnergy(G4double);

private:
	G4ParticleGun *fParticleGun;
	G4double fPrimaryEnergy;
};
#endif



