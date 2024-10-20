#ifndef VOLUMETOOLBTN_H
#define VOLUMETOOLBTN_H

#include"SliderWidget.h"

#include <QToolButton>
#include <memory>
#include<QMouseEvent>

class QTimer;
class QLabel;
class QVBoxLayout;

class VolumeToolBtn : public QToolButton {
    Q_OBJECT
public:
    explicit VolumeToolBtn(QWidget *parent = nullptr);
    ~VolumeToolBtn() override;
    void initVolumeWidget();
    void initUi();
    void checkMousePosition();
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void showEvent(QShowEvent *event) override;
public slots:
    void onNoVolume(bool flag);
signals:
    void volumeChange(int value);
private:
    bool m_isNoVolume = false;
    std::unique_ptr<MyWidget>m_volumeWidget;
    std::unique_ptr<QLabel>m_volumeLab;
    std::unique_ptr<SliderWidget>m_volumeSlider;
    QVBoxLayout* m_vBoxLayout{};
    QPoint m_volumePosition;
    QWidget* m_volumeParent{};
    QTimer* m_leaveTimer{};
    QTimer *m_positionCheckTimer;  // 检查鼠标位置是否在m_volumeWidget上面
};


#endif //VOLUMETOOLBTN_H
