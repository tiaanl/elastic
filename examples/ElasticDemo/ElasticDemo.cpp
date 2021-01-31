
#include "canvas/App.h"
#include "elastic/Context.h"
#include "elastic/Renderer/Font.h"
#include "elastic/Views/ColorView.h"
#include "elastic/Views/ImageView.h"
#include "elastic/Views/LabelView.h"
#include "nucleus/FilePath.h"
#include "nucleus/Logging.h"
#include "nucleus/Memory/ScopedPtr.h"
#include "nucleus/Streams/FileInputStream.h"
#include "silhouette/Image.h"

class ElasticDemo : public ca::WindowDelegate {
public:
  ElasticDemo() : ca::WindowDelegate("ElasticDemo") {}

  void onWindowResized(const fl::Size& size) override {
    m_context.resize(size);
  }

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

    ca::Renderer* renderer = window->getRenderer();

    auto rootPath = nu::FilePath{__FILE__}.dirName().dirName() / "resources";

    nu::FileInputStream fontStream{rootPath / "liberation-mono.ttf"};
    if (!fontStream.openedOk()) {
      LOG(Error) << "Could not open font file.";
      return false;
    }

    if (!m_font.load(&fontStream, renderer, 144)) {
      return false;
    }

    nu::FileInputStream imageStream{rootPath / "elastic.png"};
    if (!imageStream.openedOk()) {
      LOG(Error) << "Could not open image file.";
      return false;
    }

    si::Image image;
    if (!image.loadFromStream(&imageStream)) {
      LOG(Error) << "Could not load image file.";
      return false;
    }

    auto textureId = si::createTextureFromImage(renderer, image);
    if (!isValid(textureId)) {
      LOG(Error) << "Could not upload texture to GPU.";
      return false;
    }

    m_image.reset(new el::Image{textureId, image.size()});

    if (!m_context.initialize(renderer)) {
      return false;
    }

    auto stackedSizerView = new el::StackedSizerView(&m_context);
    stackedSizerView->setExpansion(el::Expansion::Both);
    m_context.getRootView()->addChild(stackedSizerView);

    auto colorView1 = new el::ColorView(&m_context, ca::Color::red);
    stackedSizerView->addChild(colorView1);
    colorView1->setName("colorView1");
    colorView1->setHorizontalAlignment(el::Alignment::Center);
    colorView1->setExpansion(el::Expansion::Vertical);
    colorView1->setMinSize({100, 100});

    auto colorView2 = new el::ColorView(&m_context, ca::Color::blue);
    stackedSizerView->addChild(colorView2);
    colorView2->setName("colorView2");
    colorView2->setHorizontalAlignment(el::Alignment::Center);
    colorView2->setExpansion(el::Expansion::Horizontal);
    colorView2->setMinSize({100, 100});

    auto imageView1 = new el::ImageView(&m_context, m_image.get());
    stackedSizerView->addChild(imageView1);

    auto labelView = new el::LabelView{&m_context, "elastic", &m_font};
    stackedSizerView->addChild(labelView);
    //    labelView->setHorizontalAlignment(el::Alignment::Left);
    //    labelView->setVerticalAlignment(el::Alignment::Top);

    return true;
  }

  void onRender(ca::Renderer* renderer) override {
    m_context.render(renderer);
  }

private:
  NU_DELETE_COPY_AND_MOVE(ElasticDemo);

  el::Context m_context;
  nu::ScopedPtr<el::Image> m_image;
  el::Font m_font;
};

CANVAS_APP(ElasticDemo)
