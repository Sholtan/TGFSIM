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

	virtual void Build() const;
	virtual void BuildForMaster() const;
};

#endif