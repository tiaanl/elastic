# elastic

General purpose cross-platform UI library based on nucleus and canvas.

## Panel definition

```
skin {
  color {
    color: "#333"
    expand: "both"
  }

  boxsizer {
    orientation: "horizontal", border: "200 300", expand: "both"

    boxsizer {
      orientation: "horizontal" expand: "horizontal"

      button { text: "50000", onclick: "count(50000)@." }
      spacer { proportion: 1 }
      button { text: "40", onclick: "count(40)@." }
      spacer { proportion: 1 }
      button { text: "10", onclick: "count(10)@." }
    }

    layeredsizer {
      expand: "both", proportion: 1

      color {
        color: "#F00", expand: "both"

        list "the_list" {
          expand: "both", orientation: "vertical", itemTemplate: "another", downColor: "#00FF0099"
          vScrollBar: "listScrollBar", onItemClicked: "testing"
        }

        scrollbar "listScrollBar" {
          type: "vertical", pageonclick: true, expand: "vertical", scrollsteppage: 1
          minValue: 1, maxValue: 5, currentValue: 1
        }
      }
    }

  }
}
```
