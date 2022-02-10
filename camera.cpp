#include "camera.h"
#include <QMediaService>
#include <QMediaRecorder>
#include <QMediaMetaData>
#include <QMessageBox>
#include <QPalette>

Q_DECLARE_METATYPE(QCameraInfo)

void Camera::setup_dlg(const QSize &sz){
    setObjectName(QStringLiteral("Camera"));
    resize(sz);
    actionExit = new QAction(this);
    actionExit->setObjectName(QStringLiteral("actionExit"));
    actionStartCamera = new QAction(this);
    actionStartCamera->setObjectName(QStringLiteral("actionStartCamera"));
    actionStopCamera = new QAction(this);
    actionStopCamera->setObjectName(QStringLiteral("actionStopCamera"));
    actionSettings = new QAction(this);
    actionSettings->setObjectName(QStringLiteral("actionSettings"));
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QStringLiteral("centralwidget"));
    gridLayout_3 = new QGridLayout(centralwidget);
    gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
    stackedWidget = new QStackedWidget(centralwidget);
    stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
    stackedWidget->setSizePolicy(sizePolicy);
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    QBrush brush1(QColor(145, 145, 145, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
    stackedWidget->setPalette(palette);
    viewfinderPage = new QWidget();
    viewfinderPage->setObjectName(QStringLiteral("viewfinderPage"));
    gridLayout_5 = new QGridLayout(viewfinderPage);
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
    viewfinder = new QCameraViewfinder(viewfinderPage);
    viewfinder->setObjectName(QStringLiteral("viewfinder"));

    gridLayout_5->addWidget(viewfinder, 0, 0, 1, 1);

    stackedWidget->addWidget(viewfinderPage);
    previewPage = new QWidget();
    previewPage->setObjectName(QStringLiteral("previewPage"));
    gridLayout_4 = new QGridLayout(previewPage);
    gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
    lastImagePreviewLabel = new QLabel(previewPage);
    lastImagePreviewLabel->setObjectName(QStringLiteral("lastImagePreviewLabel"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(lastImagePreviewLabel->sizePolicy().hasHeightForWidth());
    lastImagePreviewLabel->setSizePolicy(sizePolicy1);
    lastImagePreviewLabel->setFrameShape(QFrame::Box);

    gridLayout_4->addWidget(lastImagePreviewLabel, 0, 0, 1, 1);

    stackedWidget->addWidget(previewPage);

    gridLayout_3->addWidget(stackedWidget, 0, 0, 2, 1);

    setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0, 422, 21));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuDevices = new QMenu(menubar);
    menuDevices->setObjectName(QStringLiteral("menuDevices"));
    setMenuBar(menubar);
    auto statusbar = new QStatusBar(this);
    statusbar->setObjectName(QStringLiteral("statusbar"));
    setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuDevices->menuAction());
    menuFile->addAction(actionStartCamera);
    menuFile->addAction(actionStopCamera);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    setWindowTitle(QApplication::translate("Camera", "Camera", nullptr));
    actionExit->setText(QApplication::translate("Camera", "Exit", nullptr));
    actionStartCamera->setText(QApplication::translate("Camera", "Start Camera", nullptr));
    actionStopCamera->setText(QApplication::translate("Camera", "Stop Camera", nullptr));
    actionSettings->setText(QApplication::translate("Camera", "Settings", nullptr));
    lastImagePreviewLabel->setText(QString());
    menuFile->setTitle(QApplication::translate("Camera", "File", nullptr));
    menuDevices->setTitle(QApplication::translate("Camera", "Devices", nullptr));

    QObject::connect(actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(actionSettings, SIGNAL(triggered()), this, SLOT(configureCaptureSettings()));
    QObject::connect(actionStartCamera, SIGNAL(triggered()), this, SLOT(startCamera()));
    QObject::connect(actionStopCamera, SIGNAL(triggered()), this, SLOT(stopCamera()));
    stackedWidget->setCurrentIndex(0);

    QMetaObject::connectSlotsByName(this);
};


Camera::Camera(const QSize &sz, QWidget *parent) : QMainWindow(parent){
    setup_dlg(sz);
    //Camera devices:
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        menuDevices->addAction(videoDeviceAction);
    }

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &Camera::updateCameraDevice);

    setCamera(QCameraInfo::defaultCamera());
}

void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &Camera::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &Camera::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &Camera::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &Camera::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));
    m_camera->setViewfinder(viewfinder);

    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &Camera::processCapturedImage);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &Camera::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &Camera::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &Camera::updateLockStatus);

    m_camera->start();
}

void Camera::keyPressEvent(QKeyEvent * event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        m_camera->searchAndLock();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_camera->captureMode() == QCamera::CaptureStillImage) {
            takeImage();
        } else {
            if (m_mediaRecorder->state() == QMediaRecorder::RecordingState)
                stop();
            else
                record();
        }
        event->accept();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void Camera::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        m_camera->unlock();
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}

void Camera::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    statusbar->showMessage(str);
}

void Camera::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::toggleLock()
{
    switch (m_camera->lockStatus()) {
    case QCamera::Searching:
    case QCamera::Locked:
        m_camera->unlock();
        break;
    case QCamera::Unlocked:
        m_camera->searchAndLock();
    }
}

void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        statusbar->showMessage(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        if (reason == QCamera::LockFailed)
            statusbar->showMessage(tr("Focus Failed"), 2000);
    }
}

void Camera::takeImage()
{
    m_isCapturingImage = true;
    m_imageCapture->capture();
}

void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void Camera::updateCameraState(QCamera::State state)
{
    switch (state) {
    case QCamera::ActiveState:
        actionStartCamera->setEnabled(false);
        actionStopCamera->setEnabled(true);
        actionSettings->setEnabled(true);
        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        actionStartCamera->setEnabled(true);
        actionStopCamera->setEnabled(false);
        actionSettings->setEnabled(false);
    }
}

void Camera::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void Camera::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder()
{
    stackedWidget->setCurrentIndex(0);
}

void Camera::displayCapturedImage()
{
    stackedWidget->setCurrentIndex(1);
}

void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    m_isCapturingImage = false;
    if (m_applicationExiting)
        close();
}

void Camera::closeEvent(QCloseEvent *event)
{
    if (m_isCapturingImage) {
        setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}
