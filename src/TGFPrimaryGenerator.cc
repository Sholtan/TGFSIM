#include "TGFPrimaryGenerator.hh"

TGFPrimaryGenerator::TGFPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

TGFPrimaryGenerator::~TGFPrimaryGenerator()
{
	delete fParticleGun;
}

void TGFPrimaryGenerator::SetPrimaryEnergy(G4double PrimaryEnergy)
{
	fPrimaryEnergy = PrimaryEnergy;
	G4cout << G4endl << "fPrimaryEnergy in TGFPrimaryGenerator was set to " << fPrimaryEnergy << G4endl << G4endl;
	
}

void TGFPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4cout << "************** TGFPrimaryGenerator::GeneratePrimaries" << G4endl;
	

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4IonTable* Iontable = particleTable->GetIonTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(11);  // electron


	G4ThreeVector pos(0.*m,0., 0.); // тут нужно сделать координату x = 150 * m что бы проверить отсутсвие поля в world
    


	//G4double theta = (G4double)G4UniformRand()*180.*deg;
	//G4double phi = (G4double)G4UniformRand()*360.*deg;

	// Хусейн, Ильясс был прав, угол theta нужно разыгрывать равномерно по синусу 

	G4double cost = (G4double)G4UniformRand()*2. - 1.;
    G4double phi = (G4double)G4UniformRand()*360.*deg;
    G4double px = sqrt(1. - cost*cost)*cos(phi);
    G4double py = sqrt(1. - cost*cost)*sin(phi);
    G4double pz = cost;
    G4ThreeVector mom(px, py, pz);



//---------------------------------------------------
    TGFEventInformation *eventInformation = new TGFEventInformation();
    eventInformation->SetPrimaryMomentumVector(mom);
    anEvent->SetUserInformation(eventInformation);
    G4cout << "eventInformation was set" << G4endl;
//---------------------------------------------------    


    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(fPrimaryEnergy*MeV);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}



