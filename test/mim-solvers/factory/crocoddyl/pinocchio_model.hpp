///////////////////////////////////////////////////////////////////////////////
//
// This file is a modified version of the pinocchio model unittests factory from
// the Crocoddyl library This modified version is used for testing purposes only
// Original file :
// https://github.com/loco-3d/crocoddyl/blob/devel/unittest/factory/pinocchio_model.cpp
//
// BSD 3-Clause License
// Copyright (C) 2023, New York University
//
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef MIM_SOLVERS_PINOCCHIO_MODEL_FACTORY_HPP_
#define MIM_SOLVERS_PINOCCHIO_MODEL_FACTORY_HPP_

#include <pinocchio/algorithm/center-of-mass.hpp>
#include <pinocchio/algorithm/centroidal-derivatives.hpp>
#include <pinocchio/algorithm/centroidal.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <pinocchio/algorithm/jacobian.hpp>
#include <pinocchio/algorithm/kinematics-derivatives.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/fwd.hpp>
#include <pinocchio/parsers/sample-models.hpp>
#include <pinocchio/parsers/srdf.hpp>
#include <pinocchio/parsers/urdf.hpp>

#include "crocoddyl/core/utils/exception.hpp"

namespace mim_solvers {
namespace unittest {

struct PinocchioModelTypes {
  enum Type {
    Hector,
    TalosArm,
    HyQ,
    Talos,
    RandomHumanoid,
    NbPinocchioModelTypes
  };
  static std::vector<Type> init_all() {
    std::vector<Type> v;
    v.reserve(NbPinocchioModelTypes);
    for (int i = 0; i < NbPinocchioModelTypes; ++i) {
      v.push_back((Type)i);
    }
    return v;
  }
  static const std::vector<Type> all;
};

std::ostream &operator<<(std::ostream &os, PinocchioModelTypes::Type type);

class PinocchioModelFactory {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  PinocchioModelFactory(PinocchioModelTypes::Type type);
  ~PinocchioModelFactory();

  void construct_model(const std::string &urdf_file = "",
                       const std::string &srdf_file = "",
                       bool free_flyer = true);

  boost::shared_ptr<pinocchio::Model> create() const;
  std::vector<std::string> get_frame_names() const;
  std::vector<std::size_t> get_frame_ids() const;
  std::size_t get_contact_nc() const;

private:
  boost::shared_ptr<pinocchio::Model>
      model_;                           //!< The pointer to the state in testing
  std::vector<std::string> frame_name_; //!< Frame name for unittesting
  std::vector<std::size_t> frame_id_;   //!< Frame id for unittesting
  std::size_t contact_nc_;              //!< Dimension of the contact
};

/**
 * @brief Compute all the pinocchio data needed for the numerical
 * differentiation. We use the address of the object to avoid a copy from the
 * "boost::bind".
 *
 * @param model[in]  Pinocchio model
 * @param data[out]  Pinocchio data
 * @param x[in]      State vector
 * @param u[in]      Control vector
 */
void updateAllPinocchio(pinocchio::Model *const model, pinocchio::Data *data,
                        const Eigen::VectorXd &x,
                        const Eigen::VectorXd &u = Eigen::VectorXd());

} // namespace unittest
} // namespace mim_solvers

#endif // MIM_SOLVERS_PINOCCHIO_MODEL_FACTORY_HPP_
