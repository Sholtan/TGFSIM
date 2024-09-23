#ifndef TGFDetectorConstruction_HH
#define TGFDetectorConstruction_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "tools/colors"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4SystemOfUnits.hh"

#include "G4Cache.hh"

class TGFElectricFieldSetup;


class TGFDetectorConstruction: public G4VUserDetectorConstruction
{
public:
	TGFDetectorConstruction();
	~TGFDetectorConstruction();

	virtual G4VPhysicalVolume *Construct();
	void SetFieldVector(G4ThreeVector);
	G4double density_on_TS = 0.81e-3;  // in g/cm3
	G4NistManager *nist = G4NistManager::Instance();

	void CreateCloud();
	void CreateAtmosphere();

	// these next 2 variables can not be changed
	const static G4int n_layers_atmosphere = 500;
	const static G4int n_layers_cloud = 300;


private:
	G4LogicalVolume *flogicWorld;
	G4LogicalVolume *fLogicCloud[n_layers_cloud];
	G4LogicalVolume *fLogicAtmosphere[n_layers_atmosphere];

	

	G4Cache<TGFElectricFieldSetup*> fEmFieldSetup;

	virtual void ConstructSDandField();

	G4ThreeVector fFieldVector;
};

#endif



