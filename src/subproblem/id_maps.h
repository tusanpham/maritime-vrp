//  Created by Alberto Santini on 18/09/13.
//  Copyright (c) 2013 Alberto Santini. All rights reserved.
//

#ifndef ID_MAPS_H
#define ID_MAPS_H

#include <memory>
#include <boost/utility/result_of.hpp>
#include <boost/property_map/property_map.hpp>
#include "../base/graph.h"

namespace mvrp {
    class NodeIdFunctor {
        std::shared_ptr<const Graph> g;

    public:
        typedef int result_type;

        NodeIdFunctor(std::shared_ptr<const Graph> g) : g(g) {}

        result_type operator()(const Vertex &v) const {
            return g->graph[v]->boost_vertex_id;
        }
    };

    class ArcIdFunctor {
        std::shared_ptr<const Graph> g;

    public:
        typedef int result_type;

        ArcIdFunctor(std::shared_ptr<const Graph> g) : g(g) {}

        result_type operator()(const Edge &e) const {
            return g->graph[e]->boost_edge_id;
        }
    };

    template<typename Fun, typename Arg>
    class FunctionPropertyMap {
        const Fun &f;

    public:
        typedef typename boost::result_of<Fun(Arg)>::type value_type;

        explicit FunctionPropertyMap(const Fun &f) : f(f) {}

        friend value_type get(const FunctionPropertyMap &pm, const Arg &arg) {
            return pm.f(arg);
        }

        value_type operator[](const Arg &arg) const {
            return f(arg);
        }
    };
}

namespace boost {
    template<typename Fun, typename Arg>
        struct property_traits<mvrp::FunctionPropertyMap<Fun, Arg>> {
        using value_type = typename boost::result_of<Fun(Arg)>::type;
        using reference = value_type;
        using key_type = Arg;
        using category = readable_property_map_tag;
    };
}

namespace mvrp {
    template<typename Arg, typename Fun>
    FunctionPropertyMap<Fun, Arg> make_property_map(const Fun &f) {
        return FunctionPropertyMap<Fun, Arg>(f);
    }
}

#endif