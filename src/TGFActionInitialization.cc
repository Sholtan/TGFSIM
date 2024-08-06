#include "TGFActionInitialization.hh"

TGFActionInitialization::TGFActionInitialization()
{}

TGFActionInitialization::~TGFActionInitialization()
{}
void TGFActionInitialization::BuildForMaster() const
{
    TGFRunAction* runAction = new TGFRunAction();
    SetUserAction(runAction);

}

void TGFActionInitialization::Build() const
{
	TGFPrimaryGenerator* generator = new TGFPrimaryGenerator();
	SetUserAction(generator);

	TGFRunAction* runAction = new TGFRunAction();
	SetUserAction(runAction);

	TGFEventAction* eventAction = new TGFEventAction(runAction);
	SetUserAction(eventAction);

	TGFSteppingAction* steppingAction = new TGFSteppingAction(eventAction);
    SetUserAction(steppingAction);
}