#include "TGFPrimaryGenerator.hh"

TGFPrimaryGenerator::TGFPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

TGFPrimaryGenerator::~TGFPrimaryGenerator()
{
	delete fParticleGun;
}


void TGFPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4IonTable* Iontable = particleTable->GetIonTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(11);  // electron


	G4ThreeVector pos(0.*m,0., 0.); // тут нужно сделать координату x = 150 * m что бы проверить отсутсвие поля в world
    


	G4double theta = (G4double)G4UniformRand()*180.*deg;
	G4double phi = (G4double)G4UniformRand()*360.*deg;



    G4ThreeVector mom(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta));

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(30*MeV);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}



