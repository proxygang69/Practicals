import java.util.*;

public class BellmanFord {

    // Function to implement Bellman-Ford algorithm and find shortest paths
    public static Map<Character, Integer> bellmanFord(List<int[]> edges, Map<Character, Integer> vertexMap, 
                                                      Map<Integer, Character> reverseVertexMap, 
                                                      int vertexCount, char startVertex) {
        int INF = Integer.MAX_VALUE; // Infinity value to represent unreachable nodes
        int[] distance = new int[vertexCount];  // Stores shortest distance from startVertex
        int[] predecessor = new int[vertexCount]; // Stores predecessors for path reconstruction
        Arrays.fill(distance, INF);  // Initialize all distances to infinity
        Arrays.fill(predecessor, -1);  // Initialize all predecessors to -1 (no predecessor)
        distance[vertexMap.get(startVertex)] = 0;  // Distance to the start vertex is 0

        // Relax edges (vertexCount - 1) times
        for (int i = 0; i < vertexCount - 1; i++) {
            for (int[] edge : edges) {
                int u = edge[0];  // Start vertex of the edge
                int v = edge[1];  // End vertex of the edge
                int weight = edge[2];  // Weight of the edge

                if (distance[u] != INF && distance[u] + weight < distance[v]) {
                    // If a shorter path is found, update the distance and predecessor
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                }
            }
        }

        // Check for negative-weight cycles
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            if (distance[u] != INF && distance[u] + weight < distance[v]) {
                throw new RuntimeException("Graph contains a negative-weight cycle");
            }
        }

        // Map distances back to character labels
        Map<Character, Integer> result = new HashMap<>();
        for (Map.Entry<Character, Integer> entry : vertexMap.entrySet()) {
            result.put(entry.getKey(), distance[entry.getValue()]);
        }

        // Print the shortest paths
        printPaths(startVertex, vertexMap, reverseVertexMap, predecessor);

        return result;
    }

    // Function to print the shortest path from startVertex to each vertex
    private static void printPaths(char startVertex, Map<Character, Integer> vertexMap, 
                                   Map<Integer, Character> reverseVertexMap, int[] predecessor) {
        System.out.println("Shortest paths from " + startVertex + ":");

        // Loop over each vertex and reconstruct the shortest path
        for (int i = 0; i < predecessor.length; i++) {
            if (predecessor[i] == -1 && i != vertexMap.get(startVertex)) {
                continue;  // Skip if no path
            }

            List<Character> path = new ArrayList<>();
            for (int at = i; at != -1; at = predecessor[at]) {
                path.add(reverseVertexMap.get(at));
            }

            Collections.reverse(path);  // Reverse the path to show it from start to end
            System.out.print("Path to " + reverseVertexMap.get(i) + ": ");
            for (char vertex : path) {
                System.out.print(vertex + "->");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input number of vertices
        System.out.print("Enter number of vertices: ");
        int vertexCount = scanner.nextInt();
        scanner.nextLine(); // Consume the newline character

        // Maps for vertex-to-index and index-to-vertex translation
        Map<Character, Integer> vertexMap = new HashMap<>();
        Map<Integer, Character> reverseVertexMap = new HashMap<>();
        char label = 'a';
        for (int i = 0; i < vertexCount; i++) {
            vertexMap.put(label, i);       // Map 'a' -> 0, 'b' -> 1, etc.
            reverseVertexMap.put(i, label); // Reverse map for printing paths
            label++;
        }

        // Input number of edges
        System.out.print("Enter number of edges: ");
        int noEdges = scanner.nextInt();
        scanner.nextLine(); // Consume the newline character

        // List to hold edges
        List<int[]> edges = new ArrayList<>();

        // Input edges
        System.out.println("Enter edges (start end weight): ");
        for (int i = 0; i < noEdges; i++) {
            char uChar = scanner.next().charAt(0);  // Start vertex character
            char vChar = scanner.next().charAt(0);  // End vertex character
            int weight = scanner.nextInt();         // Weight of the edge
            scanner.nextLine(); // Consume the newline character

            int u = vertexMap.get(uChar);  // Convert vertices from characters to indices
            int v = vertexMap.get(vChar);
            edges.add(new int[]{u, v, weight});  // Add edge to the list
        }

        // Input the start vertex
        System.out.print("Enter the start vertex: ");
        char startVertex = scanner.next().charAt(0);

        // Run Bellman-Ford algorithm
        Map<Character, Integer> distances = bellmanFord(edges, vertexMap, reverseVertexMap, vertexCount, startVertex);

        // Output the shortest distances from the start vertex
        System.out.println("Shortest distances from " + startVertex + ":");
        for (Map.Entry<Character, Integer> entry : distances.entrySet()) {
            char vertex = entry.getKey();
            int distance = entry.getValue();
            if (distance == Integer.MAX_VALUE) {
                System.out.println(vertex + ": INF");  // Unreachable vertex
            } else {
                System.out.println(vertex + ": " + distance);  // Shortest distance
            }
        }

        scanner.close();  // Close the scanner
    }
}
