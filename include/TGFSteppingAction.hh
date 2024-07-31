#ifndef TGFSteppingAction_HH
#define TGFSteppingAction_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "TGFEventAction.hh"
#include <map>

class TGFSteppingAction : public G4UserSteppingAction
{
public:
	TGFSteppingAction(TGFEventAction* eventaction);
	~TGFSteppingAction();

	virtual void UserSteppingAction(const G4Step*);

private:
	TGFEventAction* fEventAction;
	
};
#endif
