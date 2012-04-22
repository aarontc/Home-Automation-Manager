#ifndef IRECEIVER_H
#define IRECEIVER_H

class IReceiver {

	public:
		virtual ~IReceiver() { }

};


Q_DECLARE_INTERFACE(IReceiver, "com.MadeByAI.HomeAutomationManager.IReceiver/1.0")

#endif // IRECEIVER_H
