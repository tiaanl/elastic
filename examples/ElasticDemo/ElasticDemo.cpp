
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
    context_.resize(size);
  }

  bool onWindowCreated(ca::Window* window) override {
    if (!WindowDelegate::onWindowCreated(window)) {
      return false;
    }

    ca::Renderer* renderer = window->getRenderer();

    auto root_path = nu::FilePath{__FILE__}.dirName().dirName() / "resources";

    nu::FileInputStream font_stream{root_path / "liberation-mono.ttf"};
    if (!font_stream.openedOk()) {
      LOG(Error) << "Could not open font file.";
      return false;
    }

    if (!font_.load(&font_stream, renderer, 144)) {
      return false;
    }

    nu::FileInputStream image_stream{root_path / "elastic.png"};
    if (!image_stream.openedOk()) {
      LOG(Error) << "Could not open image file.";
      return false;
    }

    si::Image image;
    if (!image.load_from_png(&image_stream)) {
      LOG(Error) << "Could not load image file.";
      return false;
    }

    auto texture_id = renderer->createTexture(ca::TextureFormat::RGBA, image.size(),
                                              image.data().data(), image.data().size(), false);
    if (!isValid(texture_id)) {
      LOG(Error) << "Could not upload texture to GPU.";
      return false;
    }

    image_.reset(new el::Image{texture_id, image.size()});

    if (!context_.initialize(renderer)) {
      return false;
    }

    auto stacked_sizer_view = new el::StackedSizerView(&context_);
    stacked_sizer_view->setExpansion(el::Expansion::Both);
    context_.getRootView()->addChild(stacked_sizer_view);

    auto red_block = new el::ColorView(&context_, ca::Color::red);
    stacked_sizer_view->addChild(red_block);
    red_block->setName("colorView1");
    red_block->setHorizontalAlignment(el::Alignment::Center);
    red_block->setExpansion(el::Expansion::Vertical);
    red_block->setMinSize({100, 100});

    auto blue_block = new el::ColorView(&context_, ca::Color::blue);
    stacked_sizer_view->addChild(blue_block);
    blue_block->setName("colorView2");
    blue_block->setHorizontalAlignment(el::Alignment::Center);
    blue_block->setExpansion(el::Expansion::Horizontal);
    blue_block->setMinSize({100, 100});

    auto image_view = new el::ImageView(&context_, image_.get());
    stacked_sizer_view->addChild(image_view);

    auto label_view = new el::LabelView{&context_, "elastic", &font_};
    stacked_sizer_view->addChild(label_view);
    label_view->setHorizontalAlignment(el::Alignment::Left);
    label_view->setVerticalAlignment(el::Alignment::Top);

    return true;
  }

  void onRender(ca::Renderer* renderer) override {
    context_.render(renderer);
  }

private:
  NU_DELETE_COPY_AND_MOVE(ElasticDemo);

  el::Context context_;
  nu::ScopedPtr<el::Image> image_;
  el::Font font_;
};

CANVAS_APP(ElasticDemo)
