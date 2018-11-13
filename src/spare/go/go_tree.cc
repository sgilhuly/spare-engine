#include "spare/go/go_tree.h"

namespace spare {

GoTree::GoTree() : root(new Go(this)) {}

GoTree::~GoTree() { delete root; }

void GoTree::UpdateTree(float delta) { root->Traverse(delta); }

void GoTree::DrawTree() {
  if (primary_camera) {
    root->TraverseDraw(primary_camera->GetProjection(),
                       primary_camera->GetView());
  }
}

}  // namespace spare
