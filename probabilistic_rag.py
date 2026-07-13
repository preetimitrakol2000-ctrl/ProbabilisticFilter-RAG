from filter_bridge import FilterBridge

if __name__ == "__main__":
    guard = FilterBridge()

    # Register document IDs that actually exist in storage
    guard.add_key("doc_id_9921")
    guard.add_key("doc_id_1104")

    print("=== PROBABILISTICFILTER-RAG METADATA GUARD ===")
    
    test_key = "doc_id_0000"
    if not guard.contains_key(test_key):
        print(f"[*] key '{test_key}' definitely missing. Downstream Vector DB lookup skipped!")
    else:
        print(f"[*] key '{test_key}' potentially present. Routing to full vector scan.")
