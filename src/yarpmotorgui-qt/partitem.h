#ifndef PARTITEM_H
#define PARTITEM_H

#include <QWidget>
#include "flowlayout.h"
#include "sequencewindow.h"
#include "jointitem.h"
#include "piddlg.h"
#include <QTimer>
#include "robotMotorGui.h"

///////////YARP//////////
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Port.h>
#include <yarp/os/Network.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <iCub/DebugInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/Time.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Stamp.h>

using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;

#define     MAX_WIDTH_JOINT 240



class PartItem : public QWidget
{
    Q_OBJECT
public:
    explicit PartItem(QString robotName,
                      QString partName,
                      ResourceFinder *finder,
                      bool debug_param_enabled,
                      bool speedview_param_enabled,
                      bool enable_calib_all,
                      bool position_direct_enabled,
                      bool openloop_enabled,
                      QWidget *parent = 0);

    ~PartItem();

    void openSequenceWindow();
    bool cycleAllSeq();
    bool checkAndRunAllSeq();
    bool checkAndRunTimeAllSeq();
    bool checkAndCycleAllSeq();
    bool checkAndCycleTimeAllSeq();
    void runAll();
    void idleAll();
    void homeAll();
    bool checkAndHomeAll();
    void calibrateAll();
    bool checkAndGo();
    void stopSequence();
    void setTreeWidgetModeNode(QTreeWidgetItem *node);
    void loadSequence();
    void saveSequence();
    QTreeWidgetItem *getTreeWidgetModeNode();
    QString getPartName();
    QList<int> getPartMode();
    void resizeWidget(int w);

private:
    void fixedTimeMove(SequenceItem sequence);

protected:
    void resizeEvent(QResizeEvent *event);
    void changeEvent(QEvent *event );

private:
    QTreeWidgetItem *node;
    FlowLayout *layout;
    SequenceWindow *sequenceWindow;
    QString partName;
    bool positionDirectEnabled;
    bool openloopEnabled;
    PidDlg *currentPidDlg;
    Stamp sequence_port_stamp;
    QTimer runTimer;
    QTimer runTimeTimer;
    QTimer cycleTimer;
    QTimer cycleTimeTimer;

    QList<SequenceItem> runValues;
    QList<SequenceItem> runTimeValues;
    QList<SequenceItem> cycleValues;
    QList<SequenceItem> cycleTimeValues;
    int controlModes[MAX_NUMBER_OF_JOINTS];


    ResourceFinder *finder;
    Property options;
    PolyDriver *partsdd;
    PolyDriver *debugdd;

    Port      sequence_port;
    bool interfaceError;


    IPositionControl *pos;
    IPositionDirect  *iDir;
    IVelocityControl *iVel;
    IEncoders *iencs;
    IAmplifierControl *amp;
    IPidControl *pid;
    IOpenLoopControl *opl;
    ITorqueControl *trq;
    IImpedanceControl *imp;
    IDebugInterface *idbg;
    IControlLimits *lim;
    IControlCalibration2 *cal;
    IControlMode2 *ctrlmode2;
    IInteractionMode *iinteract;


    bool *CURRENT_POS_UPDATE;
    int *SEQUENCE_ITERATOR;
    double **STORED_POS;
    double **STORED_VEL;
    int     *SEQUENCE;
    int *INV_SEQUENCE;
    double    *TIMING;
    //int *index;

    uint *timeout_seqeunce_id;
    uint *timeout_seqeunce_rate;
    uint *entry_id;

    //this value are used for copy/paste operations
    double  *COPY_STORED_POS;
    double  *COPY_STORED_VEL;
    int        COPY_SEQUENCE;
    double       COPY_TIMING;

    int slowSwitcher;

signals:
    void sendPartJointsValues(int,QList<double>,QList<double>);
    void stoppedSequence();
    void cycleSequence();
    void cycleTimeSequence();
    void runTimeSequence();
    void runSequence();
    void setCurrentIndex(int);
    void sequenceActivated();
    void sequenceStopped();

public slots:
    void updateControlMode();
    void updatePart();
    void onViewSpeedValues(bool);

private slots:
    void onSequenceActivated();
    void onSequenceStopped();
    void onStopSequence();
    void onCycleTimeTimerTimeout();
    void onCycleTimerTimeout();
    void onRunTimerTimeout();
    void onRunTimeout();
    void onGo(SequenceItem);
    void onOpenSequence();
    void onSaveSequence(QList<SequenceItem> values);
    void onSequenceRunTime(QList<SequenceItem>);
    void onSequenceRun(QList<SequenceItem> values);
    void onSequenceCycle(QList<SequenceItem>);
    void onSequenceCycleTime(QList<SequenceItem>);
    void onCalibClicked(JointItem *joint);
    void onJointChangeMode(int mode,JointItem *joint);
    void onJointInteraction(int interaction,JointItem *joint);
    void onSliderPositionMoved(double pos, double vel, int index);
    void onSliderTorqueMoved(double torqueVal,int index);
    void onSliderOpenloopMoved(double torqueVal,int index);
    void onSliderVelocityMoved(double speedVal,int index);
    void onSequenceWindowDoubleClicked(int sequenceNum);
    void onHomeClicked(JointItem *joint);
    void onIdleClicked(JointItem *joint);
    void onRunClicked(JointItem *joint);
    void onPidClicked(JointItem *joint);
    void onSendPid(int jointIndex, Pid newPid);
    void onSendTorque(int jointIndex, Pid newPid, double newBemfGain);
    void onSendStiffness(int jointIdex, double stiff, double damp, double force);
    void onSendOpenLoop(int jointIndex, int openLoopVal);


};

#endif // PARTITEM_H
