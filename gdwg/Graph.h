/*
* Sam Wemyss
* z5019350
*/
#ifndef GDWG_H
#define GDWG_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace gdwg {
   template <typename N, typename E>
   class Graph {
   public:
      Graph() = default;
      Graph(const Graph&);
      Graph(Graph&&);

      Graph& operator=(const Graph&);
      Graph& operator=(Graph&&);

      bool addNode(const N& val);
      bool addEdge(const N& src, const N& dst, const E& w);
      bool replace(const N& oldData, const N& newData);
      void mergeReplace(const N& oldData, const N& newData);
      void deleteNode(const N&) noexcept;
      void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
      void clear() noexcept;
      bool isNode(const N& val) const;
      bool isConnected(const N& src, const N& dst) const;
      void printNodes() const;
      void printEdges(const N& val) const;

      void begin() const { it = nodes.cbegin(); }
      bool end() const { return it == nodes.cend(); }
      void next() const { ++it; }
      const N& value() const { return it->first; }

   private:
      class Node;
      class Edge {
      public:
         Edge(const E& w) : weight{w} {}
         Edge(std::shared_ptr<Node> to, const E& w)
            : dst{to}, weight{w}
         {
         }

         const E& getWeight() const { return weight; }
         const N& getDstValue() const;
         void setDstPtr(std::shared_ptr<Node> sp);
         bool isDanglingEdge() const { return dst.expired(); }

      private:
         std::weak_ptr<Node> dst {};
         E weight;
      };
      class Node {
      public:
         Node(const N& val) : value{val} {}

         unsigned int getDegree() const { return outgoingEdges.size(); }
         const N& getValue() const { return value; }
         void setValue(const N& val) { value = val; }
         void addOutgoingEdge(const Edge& e);
         bool edgeExists(const N& dst, const E& w) const;
         bool anyEdgeExists(const N& dst) const;
         void deleteOutgoingEdge(const E& w, const N& dst);
         void purgeDanglingEdges();
         const std::vector<std::shared_ptr<Edge>>& getOutgoingEdges() const { return outgoingEdges; }

      private:
         std::vector<std::shared_ptr<Edge>> outgoingEdges {};
         N value;
      };

      std::unordered_map<N, std::shared_ptr<Node>> nodes {};
      mutable typename std::unordered_map<N, std::shared_ptr<Node>>::const_iterator it {};

      const std::shared_ptr<Node>& getNodePtr(const N& n) const { return nodes.find(n)->second; }
      void swap(Graph& other);
   };

   #include "Graph.tem"

}

#endif // GDWG_H
